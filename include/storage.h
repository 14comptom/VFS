/*
*FILE:      *storage.h
*AUTHOR:    *Comptom
*NOTES:     *Checks whether storage exists and if not, create and write
            *metadata
            
*WARNINGS   *
*LICENCE    *Licensed under MIT License.
*/

#ifndef STORAGE_H
#define STORAGE_H

#define PATH_BUFFER_SIZE 256
int vfs_storage_init(void);

#endif