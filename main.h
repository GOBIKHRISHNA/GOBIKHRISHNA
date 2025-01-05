#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
 

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3
#define FG          4
#define BG          5
#define JOBS        6


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//create a 2d array

void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
void echo(char *input_string);
void execute_internal_commands(char *input_string);
void execute_external_commands(char *input_string);




void signal_handler(int signum);
void extract_external_commands(char **external_commands);

//create a struct data
typedef struct dat
{
    char command[100];
    int pid;
    struct dat *link;
}Slist;


//function prototypes
int insert_first(Slist **head, char *str, int pid);
void print_list(Slist *head);
int delete_first(Slist **head);


void fg(Slist *head);
void bg(Slist *head);
void jobs(Slist *head);

#endif