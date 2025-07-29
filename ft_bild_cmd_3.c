#include "minishell.h"

int	ft_handle_command(t_command *cmd, t_shell *shell, int *prev_fd)
{
	int	pipefd[2];

	if (!cmd->argv || !cmd->argv[0])
		return (ft_handle_empty_cmd(cmd));
	if (ft_bild_cmd_out_fork(cmd->argv, shell))
		return (0);
	if (cmd->pip && pipe(pipefd) < 0)
		return (perror("pipe"), -1);
	return (ft_fork_and_manage(cmd, shell, pipefd, prev_fd));
}

void    safe_exit(int status)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}
