#include "minishell.h"

void	clear_tokens(t_token **head)
{
	t_token *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->value);
		free(tmp);
	}
}
void cleanup_loop(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	shell->line = NULL;

	clear_tokens(&(shell->tokens));
	shell->tokens = NULL;
}

