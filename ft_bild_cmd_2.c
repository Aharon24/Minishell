#include "minishell.h"

int	ft_handle_empty_cmd(t_command *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->has_heredoc)
		close(cmd->heredoc_fd);
	if (check_redirections(cmd, fd) == -1)
		g_exit_status = 1;
	return (0);
}

int	ft_fork_and_manage(t_command *cmd, t_shell *shell,
			int pipefd[2], int *prev_fd)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, handle_sigcat);
	signal(SIGQUIT, SIG_DFL);
	if (pid == 0)
		ft_child(cmd, shell, pipefd, *prev_fd);
	else if (pid > 0)
		ft_parent(cmd, prev_fd, pipefd);
	else
		return (perror("fork"), -1);
	return (0);
}

void	ft_child(t_command *cmd, t_shell *shell,
			int pipefd[2], int prev_fd)
{
	if (cmd->pip)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (cmd->has_heredoc)
		dup2(cmd->heredoc_fd, STDIN_FILENO);
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (handle_redirections(cmd) == -1)
		exit(1);
	ft_exec_or_exit(cmd, shell);
}

void	ft_exec_or_exit(t_command *cmd, t_shell *shell)
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
	ft_built_in_faind(cmd->argv, shell);
	exit(g_exit_status);
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
