// File: src/io_host.c
#include "cli/core.h"     // adjust path if needed
#include <stdio.h>

// Nonblocking read: return -1 if no key available.
int cli_read_char_nonblocking(void) {
    if (!_kbhit()) return -1;
    return _getch();
}

void cli_write_char(char c) {
    putchar(c);
}

void cli_write_str(const char *s) {
    fputs(s, stdout);
}

void cli_sleep_ms(int ms) {
    Sleep(ms);
}
