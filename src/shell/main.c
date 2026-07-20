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

void start_VFS(void){
    vfs_storage_init();

}
int main(void){
    printf("VFS starting...\n");
    utils_sleep(400);

    start_VFS();
}


