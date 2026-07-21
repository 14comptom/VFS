/*
    *FILE:       main.c
    *AUTHOR:     Comptom
    *NOTES:      
    *WARNINGS   *
                
    *LICENCE    *Licensed under MIT License.
*/

#include <stdio.h>

#include "utils.h"
#include "storage.h"
#include "shell.h"

void start_VFS(void){
    vfs_storage_init();
    vfs_shell_init();

}
int main(void){
    utils_print_color(stdout, "Starting vfs....", color_cyan);
    utils_sleep(400);

    start_VFS();
}


