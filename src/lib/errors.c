/*
  *File: Errors.c
  * Definition of system errors and look up table for message
  *and action of defined error

  Warning: Giant look up table.
    */

#include <stdbool.h>
#include "errors.h"
#include "utils.h"


/*
    * Erors defined in VFS/include/errors.h
 */
typedef enum {
    INFO,
    WARNIGN,
    ERROR,
} ErrorType;

int file_not_found(void *data, bool messgae) {
    return 0;
}
typedef struct {
    const char* messgae;
    int(*handler) (void *data, bool message); /*
        *true prints message using functon utils_print_color from
        *VFS/lib/utils.c false otherwise
        */
    ErrorType error_type;

} ErrorInfo;

/* Print message of errors color coded based in type.  */
void print_message(const ErrorInfo* erro_info) {
    int color;

    switch (erro_info->error_type) {
        case INFO:
            color = color_green;
            break;
        case WARNIGN:
            color = color_yellow;
            break;
        case ERROR:
            color = color_red;
            break;
        default:
            break;
    }

    utils_print_color(stderr, erro_info->messgae, color);
}

static const ErrorInfo erro_info[ENUM_COUNT] = {
  [FILE_NOT_FOUND]  = {
      .messgae = "[WARNING] DISK: File not found\n",
      .handler = file_not_found,
      .error_type = WARNIGN,
  },

  [PERMISSION_DENIED] = {
      .messgae = "[WARNING] SHELL: Permission denied\n",
      .error_type = WARNIGN,
  },

  [DISK_NOT_FOUND] = {
      .messgae = "[WARNING] DISK: Disk not found\n",
      .error_type = WARNIGN,
  },

  [CREATING_DISK] = {
      .messgae = "[INFO]: DISK: Creating disk and writing metadata\n",
      .error_type = INFO,
  },

  [DISK_FOUND] = {
      .messgae = "[INFO] DISK: Disk found and ready to use!\n",
      .error_type = INFO,
  },

  [FAILED_TO_GET_DISK_PATH] = {
      .messgae = "[ERROR] DIsk: Failed to get disk path\n",
      .error_type =  ERROR,
  },

  [UNSUPPORTED_PLATFORM] = {
      .messgae = "[error] SYSTEM: Unsupporten Operating System\n",
      .error_type =  ERROR,
  },

  [FAILED_TO_CREATE_DISK] = {
      .messgae = "[ERROR] DISK: Failed to create and write metadata!\n",
      .error_type =  ERROR,
  },

  [UNIMPLEMENTED] = {
      .messgae = "[WARNING] SHELL: Command is not yet implemented.\n",
      .error_type =  WARNIGN,
  },

  [TOO_MANY_ARGUMENTS] = {
      .messgae = "[WARNING] SHELL: Too many arguments!\n",
      .error_type =  WARNIGN,
  },

  [NOT_A_COMMAND] = {
      .messgae = "[WARNING] SHELL: '%s' is not recognized as an"
                "internal command\n",
      .error_type = WARNIGN,
  },

  [SHELL_LOADED] = {
      .messgae = "[INFO] SHELL: Shell loaded!\n",
      .error_type = INFO,
  },

  [SHELL_STARTING] = {
      .messgae = "[INFO] SHELL: Shell starting..\n",
      .error_type = INFO,
  },

  [STARTING] = {
      .messgae = "Starting vfs....\n",
      .error_type = INFO,
  }
};


void set_error(Errors error, bool print_message_to_console) {
    if(print_message_to_console) {
        print_message(&erro_info[error]);
    }

}
