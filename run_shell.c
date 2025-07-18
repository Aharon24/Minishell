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

void	run_shell(t_shell *shell)
{
	t_command	*cmd;

	while (1)
	{
		shell->line = readline("minishell -> ");
		if (!shell->line)
			break ;
		add_history(shell->line);
		if (shell->line[0] == '\0')
		{
			free(shell->line);
			continue ;
		}
		if (tokenize(shell) == -1)
		{
			printf("tokenize error\n");
			g_exit_status = 258;
			free(shell->line);
			free_tokens(&(shell->tokens));
			continue ;
		}
		cmd = split_cmd(shell->tokens, shell);
		if (!cmd)
		{
			printf("Comand Error\n");
			g_exit_status = 1;
			free(shell->line);
			free_tokens(&(shell->tokens));
			continue ;
		}
		if ( (ft_strcmp(cmd->argv[0], "exit") == 0) && (cmd->next == NULL))
		{
			shell->exit_i = ft_chesk_exit_cmd(cmd->argv);
			g_exit_status = shell->exit_i;
			exit(g_exit_status);
		}
		else if (cmd->next == NULL && is_exit_command(cmd))
		{
			//free_shell(shell);
			//free_cmd(cmd);
			exit(g_exit_status);
		}
		ft_run_cmd(cmd, shell);
		cleanup_loop(shell);
	}
	free_shell(shell);
}
