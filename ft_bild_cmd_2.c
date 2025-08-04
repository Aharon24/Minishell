/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bild_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:13 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:06:15 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_or_exit(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	handle_exit_and_builtins(cmd, shell);
	path = find_path(shell->env, cmd->argv[0]);
	if (!path)
	{
		if (cmd->pip)
			exit(127);
		write(2, "minishell: ", 11);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	g_exit_status = 0;
	envp = shell_2_char(shell->env);
	execve(path, cmd->argv, envp);
	if (cmd->pip)
		exit(126);
	write(2, "minishell: ", 11);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": Permission denied\n", 20);
	exit(126);
}

int	ft_handle_empty_cmd(t_command *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->has_heredoc)
		close(cmd->heredoc_fd);
	if (check_redirections(cmd, fd) == -1)
		g_exit_status = 1;
	g_exit_status = 0;
	return (0);
}

pid_t	ft_fork_and_manage(t_command *cmd, t_shell *shell,
			int pipefd[2], int *prev_fd)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, handle_sigcat);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_child(cmd, shell, pipefd, *prev_fd);
	}
	else if (pid > 0)
		ft_parent(cmd, prev_fd, pipefd);
	return (pid);
}

void	ft_child(t_command *cmd, t_shell *shell, int pipefd[2], int prev_fd)
{
	if (cmd->pip)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (cmd->has_heredoc)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (handle_redirections(cmd) == -1)
		exit(1);
	ft_exec_or_exit(cmd, shell);
}

void	ft_parent(t_command *cmd, int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->pip)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
		*prev_fd = -1;
	if (cmd->has_heredoc)
		close(cmd->heredoc_fd);
}
