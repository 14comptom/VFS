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

/*
    * 2 binary files are creted, metad.vfs and disk.vfs as binary files
    * metad holds metadata for all files and disk.vfs holds the actual user data
 */
#include <stdio.h>
#include <stdlib.h>


#include "storage.h"
#include "utils.h"
#include "errors.h"


#define PATH_BUFFER_SIZE 256

static int disk_exists(const char* md_p, const char* db_p){
    FILE *metad = fopen(md_p, "rb");
    FILE *disk = fopen(db_p, "rb");
    if(metad == NULL || disk == NULL){
        set_error(DISK_NOT_FOUND, true);
        set_error(CREATING_DISK, true);
        return DISK_NOT_FOUND;
    }
    else {
        set_error(DISK_FOUND, true);
    }

    fclose(metad);
    fclose(disk);

    return 0;
}

/*
    files mut either be at home or desktop for or from where the program was
    ran at.
 */

static int get_os_path(char *md_p, char* db_p){
    #if defined(__linux__) || defined(__APPLE__)
        char* home = getenv("HOME");
        if(home == NULL){
            set_error(FAILED_TO_GET_DISK_PATH, true);
            if(
                snprintf(md_p, PATH_BUFFER_SIZE, "metad.vfs") > PATH_BUFFER_SIZE
                ||
                snprintf(db_p, PATH_BUFFER_SIZE, "disk.vfs") > PATH_BUFFER_SIZE
            ) {
                set_error(FAILED_TO_CREATE_DISK, true);
                return 1;

            }
            return 0;
        }

        if(
            snprintf(md_p, PATH_BUFFER_SIZE, "%s/metad.vfs", home) >
            PATH_BUFFER_SIZE ||
            snprintf(db_p, PATH_BUFFER_SIZE, "%s/disk.vfs", home) >
            PATH_BUFFER_SIZE
        ) {
            set_error(FAILED_TO_CREATE_DISK, true);
            return 1;
        }
        return 0;
    /*
        if disk path resolution fails at this point,
        the whole system is shut down to prevent writing to
        a non-existent file.
     */
    #elif defined(_WIN32)
        char* userprofile = getenv("USERPROFILE");
        if(userprofile == NULL){
            set_error(FAILED_TO_GET_DISK_PATH, true);
            if(
                snprintf(md_p, PATH_BUFFER_SIZE, "metad.vfs") > PATH_BUFFER_SIZE
                ||
                snprintf(db_p, PATH_BUFFER_SIZE, "disk.vfs") > PATH_BUFFER_SIZE
            ) {
                set_error(FAILED_TO_CREATE_DISK, true);
                return 1;

            }
            return 0;
        }

        if(
            snprintf(p, PATH_BUFFER_SIZE, "%s\\Desktop\\metad.vfs", userprofile)
            > PATH_BUFFER_SIZE ||
            snprintf(p, PATH_BUFFER_SIZE, "%s\\Desktop\\disk.vfs", userprofile)
            > PATH_BUFFER_SIZE
        ) {
            set_error(FAILED_TO_CREATE_DISK, true);
            return 1;
        }
        return 0;
    #else
        set_error(UNSUPPORTED_PLATFORM, true);
        return 1;
    #endif
}

static int create_disk_file(const char* md_p, const char* db_p){
    FILE *metad = fopen(md_p, "ab");
    FILE *disk = fopen(db_p, "ab");
    if(disk == NULL || metad == NULL){
        set_error(FAILED_TO_CREATE_DISK, true);
        return 1;
    }

    fclose(disk);
    fclose(metad);
    return 0;
}

int vfs_storage_init(void){
    char metad_path[PATH_BUFFER_SIZE];
    char db_path[PATH_BUFFER_SIZE];
    get_os_path(metad_path, db_path);
    // return value is ignored since failure results to system shut down.

    if(disk_exists(metad_path, db_path) == DISK_NOT_FOUND){
        create_disk_file(metad_path, db_path);
    }

    return 0;


}
