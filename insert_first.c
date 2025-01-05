#include "main.h"

int insert_first(Slist **head, char *str, int pid)
{ 
    // create node
    Slist *new = malloc(sizeof(Slist));
    // checking if memory is allocated successfully
    if (new == NULL)
    {
        return -1;
    }
    // update new node contents
    new->pid = pid;
    strcpy(new->command, str);
    new->link = NULL;
    if (*head == NULL)
    {
        *head = new;
        return 0;
    }
    // insert at first
    new->link = *head;
    *head = new;
    return 0;
}

void print_list(Slist *head)
{

    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        while (head)
        {
            printf("%s -> ", head->command);
            head = head->link;
        }

        printf("NULL\n");
    }
}

int delete_first(Slist **head)
{
    if (*head == NULL)
    {
        printf("LIST IS EMPTY\n");
        return -1;
    }
    Slist *temp = *head;
    *head = (*head)->link;
    free(temp);
}