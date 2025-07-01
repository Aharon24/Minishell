#include "minishell.h"

t_token *ft_list_add(char *data) ///// ????
{
    t_token *new;

    new = malloc(sizeof(t_token));
    new->data = data;
    new->next = NULL;
    return (new);
}


void ft_print_list(t_token *l)
{ 
    while(l)
    {
        printf("%s -> ",l->data);
        l = l->next;
    }
    printf("NULL\n");
}