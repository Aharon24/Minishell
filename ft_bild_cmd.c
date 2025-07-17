#include "minishell.h"

int	ft_bild_cmd_out_fork(char **argv,t_shell *shell)
{
	if (ft_strncmp(argv[0], "cd",2) == 0)
	{
        ft_cd(argv, shell);
		return (1);
	}
	else if (ft_strncmp(argv[0], "unset",5) == 0)
	{
		ft_unset(argv, shell);
		return (1);
	}
	else if (ft_strncmp(argv[0], "export",6) == 0)
	{
		ft_export(shell,argv);
		return (1);
	}
	else 
		return (0);
}


void	ft_built_in_faind(char **argv, t_shell *shell)
{
    if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd(argv);
    else if (ft_strncmp(argv[0], "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(argv[0], "echo", 4) == 0)
		ft_echo(argv);
	else
		ft_execve(argv, shell);
}


void ft_run_cmd(t_command *cmd, t_shell *shell)
{
	int pipefd[2];
	int prev_fd = -1;
	pid_t pid;
	int wstatus;

	while (cmd)
	{
		if (ft_bild_cmd_out_fork(cmd->argv, shell) == 1)
		{
			cmd = cmd->next;
			continue;
		}

		if (cmd->pip)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				g_exit_status = 1;
				return ;
			}
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			g_exit_status = 1;
			return;
		}
		else if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->pip)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (handle_redirections(cmd) == -1)
				exit(2);

			if (is_exit_command(cmd))
				exit(g_exit_status);

			ft_built_in_faind(cmd->argv, shell);

			exit(g_exit_status);
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
				prev_fd = -1;
		}
		cmd = cmd->next;
	}

	while (wait(&wstatus) > 0)
	{
		if (WIFEXITED(wstatus))
			g_exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			g_exit_status = 128 + WTERMSIG(wstatus);
	}
}