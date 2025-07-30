#include "minishell.h"

int	process_redirect(t_token **tokens, t_command *new_cmd, t_shell *shell)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (-1);
	redir->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	redir->filename = NULL;
	if (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		redir->filename
			= remove_quotes_and_expand((*tokens)->value, shell->env);
		*tokens = (*tokens)->next;
	}
	redir->next = NULL;
	add_redirect(&new_cmd->redirects, redir);
	return (0);
}

int	fill_argv_and_redirects(t_token **tokens,
	t_command *new_cmd, t_shell *shell)
{
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			if (fill_argv(tokens, new_cmd, shell) == -1)
				return (-1);
		}
		else if ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_HEREDOC
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_REDIRECT_APPEND)
		{
			if (fill_redirects(tokens, new_cmd, shell) == -1)
				return (-1);
		}
		else
		{
			*tokens = (*tokens)->next;
		}
	}
	return (0);
}

int	fill_redirects(t_token **tokens, t_command *new_cmd, t_shell *shell)
{
	while (*tokens && ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_HEREDOC
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_REDIRECT_APPEND))
	{
		if (process_redirect(tokens, new_cmd, shell) == -1)
			return (-1);
	}
	return (0);
}

int	fill_argv(t_token **tokens, t_command *new_cmd, t_shell *shell)
{
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		new_cmd->argv[new_cmd->argc]
			= remove_quotes_and_expand((*tokens)->value, shell->env);
		if (!new_cmd->argv[new_cmd->argc])
			return (-1);
		new_cmd->argc++;
		*tokens = (*tokens)->next;
	}
	new_cmd->argv[new_cmd->argc] = NULL;
	return (0);
}
