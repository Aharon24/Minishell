/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:07:08 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:19:54 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND || type == TOKEN_HEREDOC);
}

int	check_pipe_error(t_token *token)
{
	if (!token->next)
	{
		ft_putstr_fd("minishell: syntax error"
			" near unexpected token `newline'\n", 2);
		g_exit_status = 2;
		return (-1);
	}
	if (token->next->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error"
			" near unexpected token `|'\n", 2);
		g_exit_status = 2;
		return (-1);
	}
	return (0);
}

int	check_redirection_error(t_token *token)
{
	if (!token->next)
	{
		ft_putstr_fd("minishell: syntax error near"
			" unexpected token `newline'\n", 2);
		g_exit_status = 2;
		return (-1);
	}
	if (token->next->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (-1);
	}
	return (0);
}

int	validate_tokens(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (check_pipe_error(tokens) == -1)
				return (-1);
		}
		else if (is_redirection(tokens->type))
		{
			if (check_redirection_error(tokens) == -1)
				return (-1);
		}
		tokens = tokens->next;
	}
	return (0);
}
