/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bild_cmd_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:22 by ahapetro          #+#    #+#             */
/*   Updated: 2025/09/08 19:54:56 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit_and_builtins(t_command *cmd, t_shell *shell)
{
	int	status;

	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		status = ft_check_exit_cmd(cmd->argv);
		if (status == 257)
		{
			write(2, "exit: too many arguments\n", 26);
			safe_exit(1);
		}
		else if (status == 258)
		{
			write(2, "exit: numeric argument required\n", 33);
			safe_exit(2);
		}
		exit(status);
	}
	if (ft_strcmp(cmd->argv[0], "pwd") == 0
		|| ft_strcmp(cmd->argv[0], "env") == 0
		|| ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		ft_built_in_faind(cmd->argv, shell);
		exit(g_exit_status);
	}
}

int	handle_builtin_command(t_command *cmd, t_shell *shell, pid_t *pid_out)
{
	int	i;

	i = ft_bild_cmd_out_fork(cmd->argv, shell);
	if (i > 0)
	{
		*pid_out = -1;
		return (1);
	}
	else if (i == -1)
		return (-1);
	return (0);
}

int	handle_empty_command(t_command *cmd, int *prev_fd, pid_t *pid_out)
{
	int	pipefd[2];

	if (!cmd->argv || !cmd->argv[0])
	{
		*pid_out = -1;
		if (cmd->pip && pipe(pipefd) == 0)
		{
			close(pipefd[1]);
			if (*prev_fd != -1)
				close(*prev_fd);
			*prev_fd = pipefd[0];
		}
		ft_handle_empty_cmd(cmd);
		return (1);
	}
	return (0);
}

int	ft_handle_command(t_command *cmd, t_shell *shell,
	int *prev_fd, pid_t *pid_out)
{
	int		pipefd[2];
	pid_t	pid;
	int		res;

	res = check_command_and_permissions(shell, cmd, pid_out);
	if (res != 0)
	{
		if (res == -1)
			return (-2);
		else
			return (0);
	}
	if (cmd->pip && pipe(pipefd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	pid = ft_fork_and_manage(cmd, shell, pipefd, prev_fd);
	if (pid < 0)
		return (-1);
	*pid_out = pid;
	return (0);
}

void	safe_exit(int status)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}
