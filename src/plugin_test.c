// File: src/cli/plugin_test.c

#include "cli/command.h"
#include "cli/plugin_test.h"
#include "cli/menu.h"        // for menu_register(), menu_frame_t

#include "utils/format.h"    // for utils_format_hexdump_ex
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define TEST_BUF_SIZE 256

// A simple test buffer in RAM
static uint8_t s_test_buffer[TEST_BUF_SIZE];

// Forward declarations of the handlers
static bool cmd_test_fill_buffer(const cli_args_t *args);
static bool cmd_test_dump_buffer(const cli_args_t *args);
static bool cmd_test_write_message(const cli_args_t *args);

// Called from core_init to install these test commands
void test_cmds_init(void) {
    static const cli_command_t cmds[] = {
        { "fillbuf",  cmd_test_fill_buffer,  "Fill buffer with incremental bytes" },
        { "dumpbuf",  cmd_test_dump_buffer,  "Hex-dump the test buffer"          },
        { "writemsg", cmd_test_write_message,"Write a fixed message into buffer" },
    };
    cli_command_register(cmds, sizeof cmds / sizeof *cmds);
}  // ← closes test_cmds_init

// Called from core_init to install the test submenu
void test_menu_init(void) {
    static const menu_item_t items[] = {
        { 'F', "Fill Buffer",   "fillbuf", NULL },
        { 'D', "Dump Buffer",   "dumpbuf", NULL },
        { 'W', "Write Message", "writemsg", NULL },
        { 'B', "Back",          NULL,      NULL },
    };
    static const menu_frame_t frame = {
        .title = "Debug Tests",
        .items = items,
        .count = sizeof items / sizeof *items
    };
    menu_register(&frame);
}

// Handler: fill buffer with 0x00,0x01,0x02,… pattern
static bool cmd_test_fill_buffer(const cli_args_t *args) {
    (void)args;
    for (size_t i = 0; i < TEST_BUF_SIZE; i++) {
        s_test_buffer[i] = (uint8_t)i;
    }
    printf("Test buffer filled (0…%u)\n", TEST_BUF_SIZE - 1);
    return true;
}

// Handler: hex-dump the entire buffer
static bool cmd_test_dump_buffer(const cli_args_t *args) {
    (void)args;
    hexdump_options_t opts = {
        .bytes_per_line = 16,
        .max_rows       = 0,    // unlimited
        .show_ascii     = true
    };
    utils_format_hexdump_ex(s_test_buffer,
                             TEST_BUF_SIZE,
                             0x00000000,  // base address label
                             &opts);
    return true;
}

// Handler: write a fixed string into buffer start
static bool cmd_test_write_message(const cli_args_t *args) {
    (void)args;
    const char *msg = "Mika, Taz, Dash, Patch, Daisy (Doo), Shadow";
    size_t len = strlen(msg);
    if (len >= TEST_BUF_SIZE) len = TEST_BUF_SIZE - 1;
    memcpy(s_test_buffer, msg, len);
    s_test_buffer[len] = 0;
    printf("Wrote message: \"%s\"\n", msg);
    return true;
}
