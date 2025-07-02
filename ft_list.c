#include "minishell.h"

t_token	*ft_list_add(char *data) ///// ????
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = data;
	new->next = NULL;
	return (new);
}

void	ft_print_list(t_token *l)
{
	while (l)
	{
		printf("%s -> ", l->value);
		l = l->next;
	}
	printf("NULL\n");
}

void	ft_print_list_enum(t_token *l)
{
	if (l->type == TOKEN_WORD)
		printf("WORD\n");
	else if (l->type == TOKEN_PIPE)
		printf("PIPE\n");
	else if (l->type == TOKEN_REDIRECT_IN)
		printf("REDIRECT_IN\n");
	else if (l->type == TOKEN_REDIRECT_OUT)
		printf("REDIRECT_OUT\n");
	else if (l->type == TOKEN_REDIRECT_APPEND)
		printf("REDIRECT_APPEND\n");
	else if (l->type == TOKEN_HEREDOC)
		printf("HEREDOC\n");
	else
		printf("UNKNOWN\n");
}

void	ft_print_enum(t_token *l)
{
	t_token	*n;

	n = NULL;
	n = l;
	while (n)
	{
		ft_print_list_enum(n);
		n = n->next;
	}
}
