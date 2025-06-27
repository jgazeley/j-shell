// File: include/cli/menu.h
#ifndef CLI_MENU_H
#define CLI_MENU_H

#include <stddef.h>
#include <stdbool.h>

#define MAX_MENU_DEPTH 5
#define MAGIC_KEY  0xA5

/** One entry in a menu frame **/
typedef struct menu_item_t {
    char                    key;       /**< Character to select this entry */
    const char             *desc;      /**< Description shown in the menu */
    const char             *cmd_name;  /**< Name for cli_command_run(), or NULL */
    const struct menu_frame_t *submenu;/**< Submenu to push, or NULL */
} menu_item_t;

/** A menu frame: title + array of entries **/
typedef struct menu_frame_t {
    const char      *title;   /**< Menu title */
    const menu_item_t *items; /**< Array of items */
    size_t           count;   /**< Number of items */
} menu_frame_t;

/** Stack entry: a pointer to the current menu frame */
typedef struct {
    const menu_frame_t *frame;
} menu_stack_entry_t;

// core menu engine
void menu_init(const menu_frame_t *frame);
void menu_render(void);
bool menu_input(char ch);

// your two "instances" livedata
void menu_init_root(void);
void menu_init_debug(void);

// these tables are defined in menu_test.c
extern const menu_frame_t root_menu_frame;
extern const menu_frame_t debug_menu_frame;

void menu_register(const menu_frame_t *frame);

#endif // CLI_MENU_H
