#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//#include "storage.h"
#include "utils.h"
#include "errors.h"

#define INPUT_BUFFER_SIZE 256
#define OUTPUT_BUFFER_SIZE 2048
#define MAX_ARGUMENTS 16

typedef struct {
    int argc;   /*track the number of parametrs*/
    char* argv[MAX_ARGUMENTS]; /*pointer to input characters*/
} Command;


char* prompt_user(char* ib) {
    printf("&vfs> ");
    fflush(stdout);

    if (fgets(ib, INPUT_BUFFER_SIZE, stdin) != NULL) {
        ib[strcspn(ib, "\r\n")] = '\0';

        if (ib[0] == '\0') {
            return NULL;
        }
        return ib;
    }
    return NULL;
}

int tokenize_input(char* ib, Command *uc ) {
    uc->argc = 0;
    char* src=ib;
    int inquotes = 0;

    while(*src != '\0') {
        //skip whitespace or tab.
        while((*src == ' ' || *src == '\t') && !inquotes) {
            src+=1;
        }
        if (*src == '\0') break;

        if (*src == '\"') {
            inquotes = 1;
            src++; // Step past opening quote '"'

            // Skip leading spaces or tabs INSIDE the quote
            while ((*src == ' ' || *src == '\t') && *src != '\0') {
                src++;
            }
        }
        if (*src == '\0') break; // break if " has no value after.

        if(uc->argc >= MAX_ARGUMENTS - 1) { // final index for null
            set_error(EXCESS_ARGUMENTS, true);
            //Set error and return excess arguments error code.
            return EXCESS_ARGUMENTS;
        }

        uc->argv[uc->argc] = src;
        uc->argc+=1;

        // 6. Inner loop: Scan until token delimiter or closing quote
        while (*src != '\0') {
            // Closing quote: cut string, reset quote flag, advance past quote
            if (*src == '\"' && inquotes) {
                *src = '\0';
                inquotes = 0;
                src++;
                break;
            }

            // Unquoted delimiter (space or tab): cut string and advance
            if ((*src == ' ' || *src == '\t') && !inquotes) {
                *src = '\0';
                src++;
                break;
            }

            src++;
        }
    }
    uc->argv[uc->argc] = NULL;

    /* for(int i=0; i<uc->argc; i+=1) {
        printf("%s\n", uc->argv[i]);
    } */
    return 0;
}

/*
    Funtion calls to specific commands
    number of parameters are checked here to prevent excess
    parameters to the specific command.
*/
int cmd_ls(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_mkdir(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_cd(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_touch(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_sudo(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_sysshut(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_cat(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_pwd(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}

int cmd_man(Command *uc) {
    printf("%s\n", uc->argv[0]);
    set_error(UNIMPLEMENTED,true);
    return 0;
}




int process_command(char* ib) {
    Command user_commands;

    if (tokenize_input(ib, &user_commands) != 0) {
        utils_print_color(stderr, "[WARNING] SHELL: Too many arguments!\n",
                        color_yellow);
        set_error(EXCESS_ARGUMENTS, true);
        return 1;
    }

    if (user_commands.argc == 0) {
        return 0;
    }

    if(strcmp(user_commands.argv[0], "ls") == 0) return cmd_ls(&user_commands);
    if(strcmp(user_commands.argv[0], "mkdir") == 0) return
                                                    cmd_mkdir(&user_commands);
    if(strcmp(user_commands.argv[0], "touch") == 0) return
                                                    cmd_touch(&user_commands);
    if(strcmp(user_commands.argv[0], "cd") == 0) return cmd_cd(&user_commands);
    if(strcmp(user_commands.argv[0], "sudo") == 0) return
                                                    cmd_sudo(&user_commands);
    if(strcmp(user_commands.argv[0], "sysshut") == 0) return
                                                    cmd_sysshut(&user_commands);
    if(strcmp(user_commands.argv[0], "cat") == 0) return
                                                    cmd_cat(&user_commands);
    if(strcmp(user_commands.argv[0], "pwd") == 0) return
                                                    cmd_pwd(&user_commands);
    if(strcmp(user_commands.argv[0], "man") == 0) return
                                                    cmd_man(&user_commands);
    else {
    char msg[128];
    snprintf(msg, sizeof(msg), "[WARNING] SHELL: '%s' is not recognized as an"
                                "internal command",
             user_commands.argv[0]);
    // Avoided VFS/include/errors.h
    utils_print_color(stderr, msg, color_yellow);
    }





    return 0;
}

void display_text(void){

}

void start_session(void){
    char input_buffer[INPUT_BUFFER_SIZE];
    //bool active_sesseion = true;
    while(1){
        if(prompt_user(input_buffer) == NULL) {
            continue;
        }

        process_command(input_buffer);

        display_text();
    }
}

 int vfs_shell_init(void) {
    utils_print_color(stderr, "[INFO] SHELL: Shell loaded!", color_green);
    set_error(SHELL_LOADED, true);
    utils_sleep(200);
    set_error(SHELL_STARTING, true);

    start_session();

    return 0;
}
