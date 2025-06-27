#include "cli/menu.h"
#include "cli/menu_definitions.h"

/* — Debug submenu — */
static const menu_item_t debug_items[] = {
    { 'F', "Fill buffer",        "fillbuf",    NULL },
    { 'D', "Dump buffer",        "dumpbuf",    NULL },
    { 'W', "Write message",      "writemsg",   NULL },
    { 'B', "Back",               NULL,         NULL },
};
const menu_frame_t debug_menu_frame = {
    .title = "Debug Tests",
    .items = debug_items,
    .count = sizeof debug_items / sizeof *debug_items
};

/* — N64 submenu — */
static const menu_item_t n64_items[] = {
    { 'H', "Show header",        "n64_header", NULL },
    { 'I', "Show info",          "n64_info",   NULL },
    { 'B', "Back",               NULL,         NULL },
};
const menu_frame_t n64_menu_frame = {
    .title = "N64 Options",
    .items = n64_items,
    .count = sizeof n64_items / sizeof *n64_items
};

/* — Root menu — */
static const menu_item_t root_items[] = {
    { 'D', "Debug Tests",        NULL,           &debug_menu_frame },
    { 'G', "N64 Options",        NULL,           &n64_menu_frame   },
    { 'H', "Help",               "help",         NULL              },
    { 'X', "Exit",               "exit",         NULL              },
};
const menu_frame_t root_menu_frame = {
    .title = "Main Menu",
    .items = root_items,
    .count = sizeof root_items / sizeof *root_items
};
