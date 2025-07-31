#include "minishell.h"

int	ft_handle_command(t_command *cmd, t_shell *shell, int *prev_fd, pid_t *pid_out)
{
	int	pipefd[2];
	pid_t	pid;

	if (!cmd->argv || !cmd->argv[0])
	{
		*pid_out = -1;
		return (ft_handle_empty_cmd(cmd));
	}
	if (ft_bild_cmd_out_fork(cmd->argv, shell))
	{
		*pid_out = -1;
		return 0;
	}
	if (cmd->pip && pipe(pipefd) < 0)
		return (perror("pipe"), -1);

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
