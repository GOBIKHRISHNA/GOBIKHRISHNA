#include "main.h"
char *get_command(char *input_string)
{
    if (input_string == NULL)
    {
        return NULL;
    }
    int size = strlen(input_string);

    char *ptr = malloc(size);
    int i = 0;

    while (1)
    {
        if (input_string[i] == '\0')
        {
            break;
        }
        ptr[i] = input_string[i];
        i++;
    }
    ptr[i] = '\0';
    return ptr;
}