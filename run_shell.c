/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:56 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:06:57 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

char	*read_input(void)
{
	char	*line;

	line = readline("minishell -> ");
	if (!line)
	{
		write(1, "exit\n", 5);
	}
	return (line);
}

int	process_line(t_shell *shell, t_command **cmd_out)
{
	add_history(shell->line);
	if (tokenize(shell) == -1)
	{
		g_exit_status = 2;
		free_tokens(&shell->tokens);
		return (1);
	}
	*cmd_out = split_cmd(shell->tokens, shell);
	if (!*cmd_out)
	{
		g_exit_status = 1;
		free_tokens(&shell->tokens);
		return (1);
	}
	return (0);
}

void	run_shell(t_shell *shell)
{
	t_command	*cmd;

	g_exit_status = 0;
	while (1)
	{
		setup_signals();
		shell->line = read_input();
		if (!shell->line)
			break ;
		if (shell->line[0] == '\0')
		{
			free(shell->line);
			continue ;
		}
		if (process_line(shell, &cmd) == 0)
			ft_run_cmd(cmd, shell);
		if (cmd)
			free_cmd(cmd);
		cleanup_loop(shell);
		free(shell->line);
	}
	free_shell(shell);
}
