#include "minishell.h"

int	ft_bild_cmd_out_fork(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return (0);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_exec_cd(argv, shell));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_exec_unset(argv, shell));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_exec_export(argv, shell));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exec_exit(argv));
	return (0);
}

void	ft_built_in_faind(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return ;
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(argv[0], "echo", 4) == 0)
		ft_echo(argv);
	else
		ft_execve(argv, shell);
}

void	print_signal_message(int sig)
{
	if (sig == 11)
		print_str("Segmentation fault\n");
	else if (sig == 2)
		write(1, "\n", 1);
	else if (sig == 3)
		print_str("Quit\n");
}

void	wait_all_and_handle(void)
{
	int		wstatus;
	pid_t	pid;
	int		sig;

	pid = wait(&wstatus);
	while (pid > 0)
	{
		if ((wstatus & 0x7f) != 0)
		{
			sig = wstatus & 0x7f;
			print_signal_message(sig);
			if (sig != 13)
				g_exit_status = 128 + sig;
		}
		else
		{
			g_exit_status = (wstatus >> 8) & 0xff;
		}
		pid = wait(&wstatus);
	}
}

void	ft_run_cmd(t_command *cmd_list, t_shell *shell)
{
	t_command	*cmd;
	int			prev_fd;

	if (read_all_heredocs(cmd_list) == -1)
		return ;
	if (validate_tokens(shell->tokens) == -1)
	{
		g_exit_status = 2;
		free_tokens(&shell->tokens);
		return ;
	}
	cmd = cmd_list;
	prev_fd = -1;
	while (cmd)
	{
		if (ft_handle_command(cmd, shell, &prev_fd) == -1)
			return ;
		cmd = cmd->next;
	}
	wait_all_and_handle();
}
