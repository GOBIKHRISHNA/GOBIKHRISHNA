
#include "main.h"

void execute_external_commands(char *input_string)
{
    char *argv[30];
    int com_pos[100]; // To store command positions
    int count = 0;
    int j = 0;
        int i=0;

//printf("--------%s\n",input_string);
    // convert input string into 2d aray
   char *token = strtok(input_string, " ");
    while (token != NULL) 
    {
        argv[i++] = token;   // Save each token (argument)
        token = strtok(NULL, " ");

    }
    argv[i] = NULL; 
    // for(int t=0;t<i;t++)
    // {
    //     printf("pipe %s\n",argv[t]); 
    // }
    // Parse command-line arguments
    com_pos[j++] = 0; // First command starts at argv[1]
    int l;
    for ( l = 0; l < i; l++)
    {
        if (strcmp(argv[l], "|") == 0)
        {
            argv[l] = NULL;       // Replace '|' with NULL to separate commands
            com_pos[j++] = l + 1; // Next command starts after '|'
            count++;
        }
    }

    int fd[2];
    int pid;
    int prev_fd=-1;
    for (int k = 0; k <= count; k++)
    {
        if (pipe(fd) == -1)
        {
            printf("Error : PIPE not created\n");
            return;
        }

        pid = fork();
        if (pid == -1)
        {
            printf("invalid\n");
            return;
        }
        else if (pid == 0)
        { // Child process
            
            if (prev_fd != -1) {
                dup2(prev_fd, 0);  // Set previous pipe's read end as stdin
                close(prev_fd);
            }
            if (k < count)
            {
                close(fd[0]);//close read
                dup2(fd[1], 1); // Set current pipe's write end as stdout
            }
           

            execvp(argv[com_pos[k]], &argv[com_pos[k]]);
        }
        else
        { // Parent process

            if(prev_fd!=-1)
            {
                close(prev_fd);
            }
            if (k < count)
            {
                close(fd[1]); // Close current pipe's write end
                prev_fd=fd[0]; // Update prev_fd to current pipe's read end
            }
            
        }
    }

    int status;
    waitpid(pid, &status, 0);
}