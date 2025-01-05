#include "main.h"

void execute_internal_commands(char *input_string)
{
    if (strncmp("exit", input_string, 5) == 0)
    {
        exit(0);
    }
    else if (strcmp("clear", input_string) == 0)
    {
        // printf("clear %s\n",input_string);
        system("clear");
    }
    else if (strncmp("pwd", input_string, 3) == 0)
    {
        system("pwd");
    }
    else if (strncmp("cd", input_string, 2) == 0)
    {
        char *string = input_string + 3;
        if (string[0] = '/')
        {
            if (chdir(string) == 0)
            {
                printf("%s directory chaged\n", string);
            }
            else
            {
                printf("Not found\n");
            }
        }
    }
    
}
void fg(Slist *head)
{   
    if(head==NULL)
    {
        printf("No jobs to resume\n");
        return ;
    }
    printf("%s\n",head->command);
    
   int pid1=fork();            // if i dint create a new process then sleep execute and come out of minisheell
    if(pid1==0)
    {
        execute_external_commands(head->command);
    }
    else if (pid1> 0) 
    {
        int status1;
        waitpid(pid1,&status1,WUNTRACED); // if no wait then execute command in background like bg
                    // if no wait then execute command in background like bg
    }
     else 
    {
        perror("Fork failed");
    }
}

//bg function
void bg(Slist *head)
{
    if(head == NULL)
    {
        printf("No jobs to resume\n");
        return;
    }
    printf("%s\n", head->command);
    int pid2;
    pid2 = fork();
    if(pid2 == 0)
    {
        execute_external_commands(head->command);
    }
}

//jobs function
void jobs(Slist *head)
{
   while(head)
   {
      printf("Stopped :%s\n", head->command);
      head = head->link;
   }
}