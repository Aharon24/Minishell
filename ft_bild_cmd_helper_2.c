/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bild_cmd_helper_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:23 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:06:24 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_not_found_errors(t_command **cmds, int *exit_codes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (exit_codes[i] == 127 && cmds[i]->pip)
		{
			write(2, "minishell: ", 11);
			write(2, cmds[i]->argv[0], ft_strlen(cmds[i]->argv[0]));
			write(2, ": command not found\n", 20);
			g_exit_status = 127;
		}
		i++;
	}
}

int	process_status(int wstatus)
{
	int	sig;

	if ((wstatus & 0x7f) != 0)
	{
		sig = wstatus & 0x7f;
		print_signal_message(sig);
		if (sig != 13)
		{
			g_exit_status = 128 + sig;
			return (128 + sig);
		}
		return (0);
	}
	else
	{
		g_exit_status = (wstatus >> 8) & 0xff;
		return (g_exit_status);
	}
}

void	collect_exit_codes(pid_t *pids, int *exit_codes, int count)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < count)
	{
		if (pids[i] != -1)
		{
			waitpid(pids[i], &wstatus, 0);
			exit_codes[i] = process_status(wstatus);
		}
		i++;
	}
}

int	run_all_commands(t_command *cmd_list, t_shell *shell,
			pid_t *pids, t_command **cmds)
{
	t_command	*cmd;
	int			prev_fd;
	int			pid_count;

	cmd = cmd_list;
	prev_fd = -1;
	pid_count = 0;
	while (cmd)
	{
		if ((!cmd->argv || !cmd->argv[0]) && cmd->next && !cmd->pip)
			cmd->pip = 1;
		if (ft_handle_command(cmd, shell, &prev_fd, &pids[pid_count]) == -1)
			return (-1);
		if (pids[pid_count] != -1)
			cmds[pid_count++] = cmd;
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (pid_count);
}
