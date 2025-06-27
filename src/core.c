// File: src/core.c
#include "cli/core.h"

#ifdef ENABLE_CLI
#include "cli/plugins.h"
#include "cli/menu.h"
#include "cli/command.h"

#if defined(PLATFORM_PICO)
  #include "pico/stdlib.h"
  #include "tusb.h"
  #include <stdio.h>
#else
  #include <stdio.h>
  #include <stdint.h>
  #include <stdbool.h>
#endif

static bool        s_ready          = false;
static bool        s_was_connected  = false;
static bool        s_banner_shown   = false;
static bool        s_cli_enabled    = false;
static bool        s_skip_once      = false;
static const char * const *s_banner_lines = NULL;
static size_t             s_banner_count = 0;
static cli_mode_t         current_mode   = CLI_MODE_MENU;

// Platform-agnostic output
#if defined(PLATFORM_PICO)
  #define cli_write_str(s) tud_cdc_write_str(s)
#else
  #define cli_write_str(s) fputs((s), stdout)
#endif

// Platform-agnostic non-blocking char read
static int cli_read_char_nonblocking(void) {
#if defined(PLATFORM_PICO)
    return getchar_timeout_us(0);
#else
    return _kbhit() ? _getch() : -1;
#endif
}

// Print the banner once
static void cli_print_banner(void) {
    if (!s_banner_lines) return;

    for (size_t i = 0; i < s_banner_count; ++i) {
        cli_write_str(s_banner_lines[i]);
        cli_write_str("\n");
    }
    cli_write_str("\n");
}

void cli_set_banner(const char * const *lines, size_t count) {
    s_banner_lines = lines;
    s_banner_count = count;
}

bool cli_core_init(void) {
    // 1) Register transport & commands
    cli_command_init();

    // 2) Let each “command plugin” register its own commands
    for (size_t i = 0; i < cli_num_command_plugins; i++) {
        cli_command_plugins[i]();
    }

    // 3) Install default banner if none provided
    static const char *default_banner[] = {
        "==============J-Shell================",
        "An Open Source Command Line Interface\n",
        "Version:    1.0.0",
        "Built:   " __DATE__,
        "Platform:    "
        #if defined(PLATFORM_PICO)
                "RP2040"
        #else
                "HOST"
        #endif
    };
    if (!s_banner_lines) {
        s_banner_lines = default_banner;
        s_banner_count = sizeof default_banner / sizeof *default_banner;
    }

    cli_print_banner();

    // 4) Show the root menu (banner waits on first connect)
    //   then let each “menu plugin” install its own frames
    for (size_t i = 0; i < cli_num_menu_plugins; i++) {
        cli_menu_plugins[i]();
    }

    // finally show the top‐level menu
    menu_init_root();

    // Avoid printing again immediately in the first cli_core_task()
    s_was_connected = true;
    s_banner_shown   = true;

    // 4) Mark ready & enabled
    s_ready       = true;
    s_cli_enabled = true;
    return true;
}

void cli_core_task(void) {
    if (!s_ready) return;

        // platform-specific polling
    #if defined(PLATFORM_PICO)
        tud_task();
        bool now_connected = tud_cdc_connected();
    #else
        bool now_connected = true;
    #endif

    if (now_connected && !s_was_connected) {
        if (!s_banner_shown) {
            cli_print_banner();
            s_banner_shown = true;
        }
        menu_init_root();
    }
    s_was_connected = now_connected;
    if (!now_connected) return;

    // If disabled, watch for key but skip exactly one
    if (!s_cli_enabled) {
        int c = cli_read_char_nonblocking();
        if (c >= 0) {
            if (s_skip_once) {
                s_skip_once = false;
            } else {
                cli_core_enable();
            }
        }
        return;
    }

    // Normal menu input
    if (current_mode == CLI_MODE_MENU) {
        int c = cli_read_char_nonblocking();
        if (c < 0 || c <= ' ') return;
        if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
        menu_input((char)c);
    }
}

bool cli_core_is_ready(void) {
    // return s_ready && tud_cdc_connected();
    return s_ready;
}

bool cli_core_is_enabled(void) {
    return s_cli_enabled;
}

void cli_core_set_mode(cli_mode_t new_mode) {
    current_mode = new_mode;
}

void cli_core_disable(void) {
    s_cli_enabled = false;
    s_skip_once   = true;         // skip the next keypress
    cli_write_str("Leaving CLI mode. Press any key to re-enter.\n\n");
}

void cli_core_enable(void) {
    s_cli_enabled = true;
    cli_print_banner();
    menu_init_root();
}

#endif /* ENABLE_CLI */