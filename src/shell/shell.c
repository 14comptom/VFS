#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "storage.h"
#include "utils.h"

#define INPUT_BUFFER_SIZE 256
#define OUTPUT_BUFFER_SIZE 2048
#define MAX_ARGUMENTS 16

typedef struct {
    int argc;   /*track the number of parametrs*/
    char* argv[MAX_ARGUMENTS]; /*pointer to input characters*/
} command;


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

int tokenize_input(char* ib, command *uc) {
    uc->argc = 0;
    int in_quotes = 0;
    int i = 0;

    /*
        Make sure input is read only up to the end of the input
        and stop the loop.
    */
    while(ib[i] != '\0') {
        while(ib[i] == ' ') {
            i++;
        }

        if(ib[i] == '\0') { /*prevent infinite assignment.*/
            break;
        } 

        uc->argv[uc->argc] = &ib[i];

        while(ib[i] != '\0') {
            if(ib[i] == '"') {
                in_quotes = !in_quotes;
            }
            else if(ib[i] == ' ' && !in_quotes) {
                break;
            }
            i++;
        }

        if (ib[i] == ' ') {
            ib[i] = '\0';
            i++;
        }
        uc->argc++;

        if(uc->argc >= MAX_ARGUMENTS) {
            return 1;
        }

    }
    return 0;
}

/*
    Funtion calls to specific commands
    number of parameters are checked here to prevent excess 
    parameters to the specific command.
*/
int cmd_ls(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_mkdir(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_cd(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_touch(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_sudo(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_sysshut(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_cat(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_pwd(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}

int cmd_man(command *uc) {
    printf("%s\n", uc->argv[0]);
    utils_print_color(stderr, "[WARNING] SHELL: Command is not yet implemented.", 
                     color_yellow);
    return 0;
}




int process_command(char* ib) {
    command user_commands;

    if (tokenize_input(ib, &user_commands) != 0) {
        utils_print_color(stderr, "[WARNING] SHELL: Too many arguments!\n", 
                        color_yellow);
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

 int vfs_shell_init() {
    utils_print_color(stderr, "[INFO] SHELL: Shell loaded!", color_green);
    utils_sleep(200);
    utils_print_color(stderr, "[INFO] SHELL: Shell starting..\n", color_green);

    start_session();

    return 0;
}