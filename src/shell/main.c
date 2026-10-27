/*
    *FILE:       main.c
    *AUTHOR:     Comptom
    *NOTES:
    *WARNINGS   *

    *LICENCE    *Licensed under MIT License.
*/

//#include <stdio.h>

#include "utils.h"
#include "storage.h"
#include "shell.h"
#include "errors.h"

#include <stdbool.h>

void start_VFS(void){
    vfs_storage_init();
    vfs_shell_init();

}
int main(void){
    set_error(STARTING, true);
    utils_sleep(400);

    start_VFS();
}
