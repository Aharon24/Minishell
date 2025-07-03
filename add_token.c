#include "minishell.h"

t_token	*add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*last;

	if (!value)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}
