// File: include/cli/plugin_test.h

#ifndef CLI_PLUGIN_TEST_H
#define CLI_PLUGIN_TEST_H

#include "cli/menu.h"    // for menu_register(), menu_frame_t
#include "cli/command.h" // for cli_command_register()

/** Register the generic “test” commands (fillbuf, dumpbuf, writemsg). */
void test_cmds_init(void);

/** Register the generic “test” submenu under the root menu. */
void test_menu_init(void);

#endif // CLI_PLUGIN_TEST_H
