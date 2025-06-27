// File: src/cli/plugins.c
#include "cli/plugins.h"

// always available:
void test_cmds_init(void);
void test_menu_init(void);

#if PLATFORM_PICO
// only when building for the Pico:
void n64_cmds_init(void);
void n64_menu_init(void);
#endif

// Fill in the arrays:
const cli_plugin_fn cli_command_plugins[] = {
    test_cmds_init,
#if PLATFORM_PICO
    n64_cmds_init,
#endif
};
const size_t cli_num_command_plugins =
    sizeof cli_command_plugins / sizeof *cli_command_plugins;

const cli_plugin_fn cli_menu_plugins[] = {
    test_menu_init,
#if PLATFORM_PICO
    n64_menu_init,
#endif
};
const size_t cli_num_menu_plugins =
    sizeof cli_menu_plugins / sizeof *cli_menu_plugins;
