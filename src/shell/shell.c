#include <stdio.h>

#include "storage.h"
#include "utils.h"

 int vfs_shell_init() {
    utils_print_color(stderr, "[INFO] SHELL: Shell loaded!", color_green);
    utils_sleep(200);
    utils_print_color(stderr, "[INFO] SHELL: Shell starting..\n", color_green);

    return 0;
}