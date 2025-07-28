#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TOKEN: %-15s TYPE: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

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

void	handle_sigcat(int signum)
{
	(void)signum;
	g_exit_status = 130;
	//write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay();
}

void	handle_sigint(int signum)
{
	(void)signum;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	validate_tokens(t_token *tokens)
{
	t_token *cur = tokens;

	if (!cur)
		return (0);
	if (cur->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	while (cur)
	{
		if (cur->type == TOKEN_PIPE && (!cur->next || cur->next->type == TOKEN_PIPE))
		{
			if (cur->next == NULL)
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

void run_shell(t_shell *shell)
{
    t_command *cmd;

    while (1)
    {
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, SIG_IGN);

		g_exit_status = 0;
        shell->line = readline("minishell -> ");
        if (!shell->line)
        {
            write(1, "exit\n", 5);
            break;
        }

        if (shell->line[0] == '\0')
        {
            free(shell->line);
            continue;
        }

        add_history(shell->line);

        if (tokenize(shell) == -1)
        {
            write(2, "minishell: syntax error\n", 25);
            g_exit_status = 258;
            free_tokens(&shell->tokens);
            free(shell->line);
            continue;
        }

        if (validate_tokens(shell->tokens) == -1)
        {
            g_exit_status = 2;
            free_tokens(&shell->tokens);
            free(shell->line);
            continue;
        }

        cmd = split_cmd(shell->tokens, shell);
        if (!cmd)
        {
            g_exit_status = 1;
            free_tokens(&shell->tokens);
            free(shell->line);
            continue;
        }

        ft_run_cmd(cmd, shell);

        cleanup_loop(shell);
        free(shell->line);
    }

    free_shell(shell);
}