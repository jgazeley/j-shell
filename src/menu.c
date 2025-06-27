// File: src/cli/menu.c
#include "cli/menu.h"
#include "cli/command.h"
#include "cli/core.h"

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

// Define the actual menu stack and stack pointer
menu_stack_entry_t stack[MAX_MENU_DEPTH];
int                 sp = -1;

void menu_init(const menu_frame_t *frame) {
    sp = 0;
    stack[0].frame = frame;
    menu_render();
}

void menu_render(void) {
    const menu_frame_t *f = stack[sp].frame;
    printf("\n=== %s ===\n", f->title);
    for (size_t i = 0; i < f->count; i++) {
        char key = f->items[i].key;
        if (key >= 32 && key <= 126) {
            printf(" %c) %s\n", key, f->items[i].desc);
        } else {
            printf("0x%02X) %s\n", (uint8_t)key, f->items[i].desc);
        }
    }
    printf("\nSelect: ");
    fflush(stdout);
}

bool menu_input(char ch) {
    // 0) Intercept magic key for direct command
    if ((uint8_t)ch == MAGIC_KEY) {
        cli_command_run("streambuf", NULL);
        menu_render();
        return true;
    }

    const menu_frame_t *f = stack[sp].frame;
    for (size_t i = 0; i < f->count; i++) {
        const menu_item_t *it = &f->items[i];
        if (it->key != ch) continue;

        if (it->cmd_name) {
            cli_command_run(it->cmd_name, NULL);
            if (!cli_core_is_enabled()) return true;
        } else if (it->submenu) {
            if (sp + 1 < MAX_MENU_DEPTH) {
                stack[++sp].frame = it->submenu;
            }
        } else if (sp > 0) {
            sp--;
        }
        menu_render();
        return true;
    }
    return false;
}

void menu_init_root(void) {
    menu_init(&root_menu_frame);
}

void menu_init_debug(void) {
    menu_init(&debug_menu_frame);
}

//------------------------------------------------------------------------------ 
// Minimal menu_register stub so plugins can compile&link.
// Right now just jumps straight into that submenu.
// Later you can make this actually merge plugin frames into your root menu.
void menu_register(const menu_frame_t *frame) {
    menu_init(frame);
}