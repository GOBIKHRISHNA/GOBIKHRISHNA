#include "main.h"
/*check the command is present in the builtin[] array or not
buitlin is not present means go to external [] array or not
if external not present means return no_command

*/
int check_command_type(char *command)
{
   // printf("commands %s\n", command);
    char *builtins[] = {"echo", "printf", "clear","read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval", "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source", "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

    for (int i = 0; builtins[i] != NULL; i++)
    {

        if (strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN;
        }
    }

    // external commands
    char *external_commands[200];
    extract_external_commands(external_commands);
    char *argv[30];
    int i = 0;

 char *token = strtok(command, " ");
    //  while (token != NULL)
    // {
    argv[i++] = token; // Save each token (argument)
    // token = strtok(NULL, " ");
    argv[i] = NULL;
    //}

    //printf("argv %s\n", *argv);
    for (int i = 0; external_commands[i] != NULL; i++)
    {
        if (strcmp(command, external_commands[i]) == 0)
        {

            return EXTERNAL;
        }
    }

    if(strcmp(command,"fg")==0)
    {
         return FG;
    }
    else if(strcmp(command,"bg")==0)
    {
         return BG;
    }
    else if(strcmp(command,"jobs")==0)
    {
         return JOBS;
    }
    // no commands

    if (strcmp(command, "\0") == 0)
    {
        return NO_COMMAND;
    }
    else{
        printf("%s: command not found\n",command);
        return -1;
    }
    
}