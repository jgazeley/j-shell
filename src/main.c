// File: src/main.c
#include "cli/core.h"

// Sleep ms helper
void cli_sleep_ms(int ms);

int main(void) {
    // Initialize CLI
    if (!cli_core_init()) return 1;

    // Pump the CLI in a simple loop
    while (cli_core_is_ready()) {
        cli_core_task();
        cli_sleep_ms(10);
    }
    return 0;
}
