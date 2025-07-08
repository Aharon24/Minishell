#include "minishell.h"

void	ft_built_in_faind(char **argv, t_shell *shell)
{
    if (ft_strncmp(argv[0], "cd", 2) == 0)
        ft_cd(argv, shell);
    else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd();
    else if (ft_strncmp(argv[0], "env", 3) == 0)
		ft_env(shell);
	// else if (ft_strncmp(argv[0], "export", 6) == 0)
	// 	ft_export();
	else if (ft_strncmp(argv[0], "unset", 5) == 0)
		ft_unset(argv, shell);
	// else if (ft_strncmp(argv[0], "echo", 4) == 0)
	// 	ft_echo();
	// else
	// 	ft_execve();
}


void ft_run_cmd(t_command *cmd, t_shell *shell)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->pip)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(2);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(2);
		}
		else if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (cmd->pip)
			{
				close(pipefd[0]);
				dup2(pipefd[1], 1);
				close(pipefd[1]);
			}
			if (handle_redirections(cmd) == -1)
				exit(2);
			ft_built_in_faind(cmd->argv, shell);
			exit(shell->exit_status);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->pip)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			else
			{
				prev_fd = -1;
			}
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0);
}