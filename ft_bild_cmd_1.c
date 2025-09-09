/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bild_cmd_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:07 by ahapetro          #+#    #+#             */
/*   Updated: 2025/09/08 19:09:37 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bild_cmd_out_fork(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return (0);
	if (ft_strcmp(argv[0], "cd") == 0)
	{
		if (ft_check_len_argv(argv) == 0)
			return (1);
		return (ft_exec_cd(argv, shell));
	}
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
	if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(argv[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
}

void	print_signal_message(int sig)
{
	if (sig == 11)
		print_str("Segmentation fault\n");
	else if (sig == 2)
		write(1, "\n", 1);
	else if (sig == 3)
		print_str("Quit (core dumped)\n");
}

void	wait_all_and_handle(pid_t *pids, t_command **cmds, int count)
{
	int	exit_codes[1024];

	collect_exit_codes(pids, exit_codes, count);
	print_not_found_errors(cmds, exit_codes, count);
}

void	ft_run_cmd(t_command *cmd_list, t_shell *shell)
{
	pid_t		pids[1024];
	t_command	*cmds[1024];
	int			pid_count;

	pid_count = 0;
	shell->heredoc_interrupted = 0;
	ft_init_pid(pids, cmds);
	if (read_all_heredocs(cmd_list) == -2)
	{
		shell->heredoc_interrupted = 1;
		g_exit_status = 130;
		return ;
	}
	if (validate_tokens(shell->tokens) == -1)
	{
		g_exit_status = 2;
		free_tokens(&shell->tokens);
		return ;
	}
	pid_count = run_all_commands(cmd_list, shell, pids, cmds);
	shell->hello = 0;
	if (pid_count >= 0)
		wait_all_and_handle(pids, cmds, pid_count);
}
