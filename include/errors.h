#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

typedef enum {
    /* Sart up */
    DISK_NOT_FOUND,
    CREATING_DISK,
    FAILED_TO_GET_DISK_PATH,
    UNSUPPORTED_PLATFORM,
    FAILED_TO_CREATE_DISK,
    DISK_FOUND,
    /*  Start up info*/
    STARTING,
    SHELL_LOADED,
    SHELL_STARTING,

    /*  Shell*/
    NOT_A_COMMAND,
    UNIMPLEMENTED, // For a feature not completely implemented
    TOO_MANY_ARGUMENTS,

    FILE_NOT_FOUND,
    PERMISSION_DENIED,
    DISK_FULL,
    FILE_EXISTS,
    INVALID_PATH,
    FIALED_TO_READ,
    FILE_TOO_LARGE,
    CORRUPTED_FILE_SYSTEM,
    ENUM_COUNT,
} Errors;

void  set_error(Errors error, bool print_message_to_console);
#endif
