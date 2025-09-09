/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:57 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/12 17:28:36 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			= remove_quotes_and_expand((*tokens)->value, shell->env, shell);
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
			if (fill_argv(tokens, new_cmd, shell) == -1
				&& shell->ivalid_var == 0)
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
			= remove_quotes_and_expand((*tokens)->value, shell->env, shell);
		if (!new_cmd->argv[new_cmd->argc])
			return (-1);
		if (new_cmd->argv[new_cmd->argc][0] == '\0' && shell->ivalid_var == 1)
		{
			free(new_cmd->argv[new_cmd->argc]);
			g_exit_status = 0;
			shell->ivalid_var = 0;
			*tokens = (*tokens)->next;
			continue ;
		}
		new_cmd->argc++;
		*tokens = (*tokens)->next;
	}
	new_cmd->argv[new_cmd->argc] = NULL;
	return (0);
}
