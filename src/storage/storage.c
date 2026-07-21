/*
*FILE:      *storage.c
*AUTHOR:    *Comptom
*NOTES:     *Checks whether storage exists and if not, create and write
            *metadata
            *Standard color codes are red for [ERROR]
            *green for [INFO] and yello for [WARNING]
            
*WARNINGS   *
*LICENCE    *Licensed under MIT License.
*/

#include "storage.h"

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


#define PATH_BUFFER_SIZE 256

/*
    Check if file.vfs exists. 
    if not metadata needs to be written to it before VFS starts
*/
static int disk_exists(const char* p){
    FILE *disk = fopen(p, "r");
    if(disk == NULL){
        utils_print_color(stderr, "[WARNING] DISK: Disk not found", 
                        color_yellow);
        utils_print_color(stderr,
                        "[INFO]: DISK: Creating disk and writing metadata",
                        color_green);
        return 1;
    }    
    else {
        utils_print_color(stderr, "[INFO] DISK: Disk found and ready to use!",
                        color_green);
        fclose(disk);
        return 0;
    }
}

static int get_os_path(char *p){
    #if defined(__linux__) || defined(__APPLE__)
        char* home = getenv("HOME");
        if(home == NULL){
            utils_print_color(stderr, "[ERROR] DIsk: Failed to get disk path\n",
                            color_red);
            snprintf(p, PATH_BUFFER_SIZE, "disk.vfs");
            return 0;
        }

        snprintf(p, PATH_BUFFER_SIZE, "%s/disk.vfs", home);
        return 0;
    
    #elif defined(_WIN32)
        char* userprofile = getenv("USERPROFILE");
        if(userprofile == NULL){
            utils_print_color(stderr, "[ERROR] DIsk: Failed to get disk path\n",
                            color_red);
            snprintf(p, PATH_BUFFER_SIZE, "disk.vfs");
            return 0;
        }

        snprintf(p, PATH_BUFFER_SIZE, "%s\\Desktop\\disk.vfs", userprofile);
        return 0;
    #else
        utils_print_color(stderr,
                        "[WARNING] SYSTEM: Unsupporten Operating System\n",
                        color_red);
        return 1;
    #endif
}

static int create_disk_file(const char* p){
    FILE *disk = fopen(p, "w");
    if(disk == NULL){
        utils_print_color(stderr, 
                        "[ERROR] DISK: Failed to create and write metadata!\n",
                         color_red);
        return 1;
    }

    fprintf(disk, "boot_number = 1");

    fclose(disk);
    return 0;
}

int vfs_storage_init(void){
    char path[PATH_BUFFER_SIZE];
    get_os_path(path);
    
    if(disk_exists(path) == 1){
        create_disk_file(path);
    }

    return 0;


}


