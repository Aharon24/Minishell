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

void wait_all_and_handle(pid_t *pids, t_command **cmds, int count)
{
    int wstatus;
    int sig;
    int i = 0;
    int exit_codes[1024]; // Массив для кодов выхода

    // Ждём все процессы и сохраняем коды выхода
    while (i < count)
    {
        if (pids[i] == -1)
        {
            exit_codes[i] = -1;
            i++;
            continue;
        }
        waitpid(pids[i], &wstatus, 0);

        if ((wstatus & 0x7f) != 0) // процесс завершён сигналом
        {
            sig = wstatus & 0x7f;
            print_signal_message(sig);
            if (sig != 13)
                g_exit_status = 128 + sig;
            exit_codes[i] = 128 + sig;
        }
        else // процесс завершился нормально
        {
            exit_codes[i] = (wstatus >> 8) & 0xff;
            g_exit_status = exit_codes[i];
        }
        i++;
    }

    // Теперь выводим ошибки по порядку, после всех waitpid
    i = 0;
    while (i < count)
    {
        if (exit_codes[i] == 127) // команда не найдена
        {
            write(2, "minishell: ", 11);
            write(2, cmds[i]->argv[0], ft_strlen(cmds[i]->argv[0]));
            write(2, ": command not found\n", 20);
        }
        i++;
    }
}



void ft_run_cmd(t_command *cmd_list, t_shell *shell)
{
	t_command	*cmd;
	int			prev_fd;
	pid_t		pids[1024];
	t_command	*cmds[1024];
	int			pid_count;

	if (read_all_heredocs(cmd_list) == -1)
		return ;
	if (validate_tokens(shell->tokens) == -1)
	{
		g_exit_status = 2;
		free_tokens(&shell->tokens);
		return ;
	}

	prev_fd = -1;
	pid_count = 0;
	cmd = cmd_list;
	while (cmd)
	{
		if (ft_handle_command(cmd, shell, &prev_fd, &pids[pid_count]) == -1)
			return ;
		cmds[pid_count] = cmd;
		pid_count++;
		cmd = cmd->next;
	}

	wait_all_and_handle(pids, cmds, pid_count);
}

