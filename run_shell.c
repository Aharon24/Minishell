#include "minishell.h"

// void	print_tokens(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		printf("TOKEN: %-15s TYPE: %d\n", tokens->value, tokens->type);
// 		tokens = tokens->next;
// 	}
// }

// void	print_cmd(t_command *cmd)
// {
// 	int			i;
// 	t_redirect	*redir;
// 	int			cmd_index;

// 	cmd_index = 0;
// 	while (cmd)
// 	{
// 		printf("\n=== Command %d ===\n", cmd_index++);
// 		printf("argv: ");
// 		if (cmd->argv)
// 		{
// 			i = 0;
// 			while (cmd->argv[i])
// 			{
// 				printf("[%s] ", cmd->argv[i]);
// 				i++;
// 			}
// 		}
// 		else
// 			printf("(null)");
// 		printf("\n");
// 		printf("pipe: %d\n", cmd->pip);
// 		redir = cmd->redirects;
// 		while (redir)
// 		{
// 			if (redir->type == TOKEN_REDIRECT_IN)
// 				printf("redirect in:    %s\n", redir->filename);
// 			else if (redir->type == TOKEN_REDIRECT_OUT)
// 				printf("redirect out:   %s\n", redir->filename);
// 			else if (redir->type == TOKEN_REDIRECT_APPEND)
// 				printf("redirect append: %s\n", redir->filename);
// 			else if (redir->type == TOKEN_HEREDOC)
// 				printf("heredoc:        %s\n", redir->filename);
// 			redir = redir->next;
// 		}
// 		cmd = cmd->next;
// 	}
// }
void	handle_sigint(int signum)
{
	(void)signum;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigcat(int signum)
{
	(void)signum;
	g_exit_status = 130;
	// write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	run_shell(t_shell *shell)
{
	t_command	*cmd;

	while (1)
	{
		setup_signals();
		shell->line = readline("minishell -> ");
		if (!shell->line)
		{
			printf("exit\n");
			break ;
		}
		add_history(shell->line);
		if (shell->line[0] == '\0')
			continue ;
		if (tokenize(shell) == -1)
		{
			printf("tokenize error\n");
			g_exit_status = 258;
			free_tokens(&(shell->tokens));
			continue ;
		}
		cmd = split_cmd(shell->tokens, shell);
		if (!cmd)
		{
			g_exit_status = 1;
			free_tokens(&(shell->tokens));
			continue ;
		}
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
		{
			g_exit_status = ft_check_exit_cmd(cmd->argv);
			if (g_exit_status == 257)
			{
				if (cmd->next == NULL)
					printf("exit\nexit: too many arguments\n");
				else
					printf("exit: too many arguments\n");
				g_exit_status = 1;
				free_cmd(cmd);
				free_tokens(&shell->tokens);
				continue ;
			}
			else if (g_exit_status == 258)
			{
				if (cmd->next == NULL)
					printf("exit\nexit: %s: numeric argument required\n", cmd->argv[1]);
				else
					printf("exit: %s: numeric argument required\n", cmd->argv[1]);
				exit(2);
			}
			else if (cmd->next == NULL)
			{
				printf("exit\n");
				exit(g_exit_status);
			}
		}
		ft_run_cmd(cmd, shell);
		cleanup_loop(shell);
	}
	free_shell(shell);
}
