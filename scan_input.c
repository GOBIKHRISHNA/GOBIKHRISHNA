#include "main.h"
char *external_commands[200];

int slp =0;
int pid;
Slist *head = NULL;
// scan the input
void scan_input(char *prompt, char *input_string)
{

    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);

    Slist *head = NULL;
    extract_external_commands(external_commands);
    while (1)
    {
        printf(" %s: ", prompt);

        // read the input
        scanf("%[^\n]s", input_string);

        getchar();

        if (strncmp(input_string, "PS1=", 4) == 0)
        {

            // Read the entire input line

            if (input_string[4] != ' ')
            {
                strcpy(prompt, &input_string[4]);
            }
            else
            {
                printf("Error: PS1 requires a value\n");
            }
            continue;
        }

        // get the command
        char *command = get_command(input_string);

        // check the Built in commands

        int ret = check_command_type(command);

        if (strncmp(command, "sleep", 5) == 0)
        {
            insert_first(&head, input_string, pid);
            slp = 1;

        }

        // printf("check cmd %d\n",ret);
        if (ret == EXTERNAL)
        {
         pid = fork();

            // child process
            if (pid == 0)
            { // printf("input %s command %s\n",input_string,command);
                signal(SIGTSTP, SIG_DFL);
                signal(SIGINT, SIG_DFL);
                execute_external_commands(input_string);
                exit(0);
            } // parent process
            else if (pid > 0)
            {
                        int status;
                waitpid(pid, &status, WUNTRACED);
                // signal(SIGINT, SIG_DFL);
            }
        }
        else if (ret == BUILTIN)
        {

            execute_internal_commands(input_string);
        }
        else if (ret == NO_COMMAND)
        {
            printf("%s: command not found \n", command);
        }
        else if (ret == FG)
        {
            fg(head);
            delete_first(&head);
        }
        else if(ret == BG)
        {
            bg(head);
            delete_first(&head);
        }
        else if(ret == JOBS)
        {
            jobs(head);
        }
        else
        {
            printf("Command not found\n");
        }

        //    if(ret == EXTERNAL || ret == BUILTIN ||strcmp(prompt,input_string) != 0){
        //             insert_first(&head,input_string);
        //    }
        echo(input_string);
        // print_list(head);
        
    }
}
void signal_handler(int signum)
{
   char prom[100] = "minishell$:";
   
    if(signum == SIGINT)
    {
        printf("\n");
        fflush(stdout);
    }  
    else if(signum == SIGTSTP)
    {
            printf("\n %s",prom);
        if(slp == 1)
        {
           insert_first(&head, "sleep", pid);
           printf("stopped %d\n",pid);
        }
    
        fflush(stdout);
    }
    else
    {
        printf("\nCommand is not executed\n");
        fflush(stdout);
    }
   
    
}
