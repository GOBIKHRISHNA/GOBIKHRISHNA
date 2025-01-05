#include"main.h"

void echo(char *input_string)
{
int status;
    //echo $$ command to valid
    if(strncmp("echo $$",input_string,7)== 0)
    {
            printf("%d\n",getpid());
    }
    else if(strncmp("echo $?",input_string,8)== 0)//echo$
    {
       printf("%d\n", WEXITSTATUS(status));
    }
    else if(strncmp("echo $SHELL",input_string,11)== 0)//echo $SHELL
    {
        char *ptr = getenv("SHELL");
        printf("%s\n",ptr);
    }
}