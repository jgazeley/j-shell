// include/cli/plugins.h
#ifndef CLI_PLUGINS_H
#define CLI_PLUGINS_H

#include <stddef.h>

// A plugin is just a function that registers commands or menus.
typedef void (*cli_plugin_fn)(void);

// These two arrays must be defined exactly once (in plugins.c)
extern const cli_plugin_fn cli_command_plugins[];
extern const size_t        cli_num_command_plugins;

extern const cli_plugin_fn cli_menu_plugins[];
extern const size_t        cli_num_menu_plugins;

#endif // CLI_PLUGINS_H
