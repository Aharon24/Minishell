/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:34 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/13 18:58:47 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_loop(t_shell *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	free_tokens(&(shell->tokens));
	shell->tokens = NULL;
}

void	free_redirects(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->filename)
			free(tmp->filename);
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	free_redirects(cmd->redirects);
	free(cmd);
}

void	free_cmd(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_command(cmd);
		cmd = tmp;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	shell->env = NULL;
	if (shell->tokens)
		free_tokens(&(shell->tokens));
	shell->tokens = NULL;
	if (shell->home)
		free(shell->home);
	shell->home = NULL;
	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = NULL;
	if (shell->old_path)
		free(shell->old_path);
	shell->old_path = NULL;
	if (shell->export)
		free_env(shell->export);
	shell->export = NULL;
	if (shell->temp)
		free(shell->temp);
	shell->temp = NULL;
}
