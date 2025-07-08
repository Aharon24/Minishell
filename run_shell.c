#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TOKEN: %-15s TYPE: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	print_cmd(t_command *cmd)
{
	int i;
	t_redirect *redir;
	int cmd_index = 0;

	while (cmd)
	{
		printf("\n=== Command %d ===\n", cmd_index++);
		printf("argv: ");
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				printf("[%s] ", cmd->argv[i]);
				i++;
			}
		}
		else
			printf("(null)");
		printf("\n");
		printf("pipe: %d\n", cmd->pip);
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == TOKEN_REDIRECT_IN)
				printf("redirect in:    %s\n", redir->filename);
			else if (redir->type == TOKEN_REDIRECT_OUT)
				printf("redirect out:   %s\n", redir->filename);
			else if (redir->type == TOKEN_REDIRECT_APPEND)
				printf("redirect append: %s\n", redir->filename);
			else if (redir->type == TOKEN_HEREDOC)
				printf("heredoc:        %s\n", redir->filename);
			redir = redir->next;
		}

		cmd = cmd->next;
	}
}


void	run_shell(t_shell *shell)
{
	t_command *cmd;

	while (1)
	{
		shell->line = readline("minishell -> ");
		if (!shell->line)
			break;
		add_history(shell->line);
		if (shell->line[0] == '\0')
		{
			free(shell->line);
			continue;
		}
		if (tokenize(shell) == -1)
			printf("Ошибка токенизации\n");
		cmd = split_cmd(shell->tokens);
		//print_cmd(cmd);
		if (is_exit_command(cmd))
		{
			//cleanup_loop(shell);
			//free_cmd(cmd);
			//free_shell(shell);
			exit(shell->exit_status);
		}
		ft_run_cmd(cmd,shell);
		cleanup_loop(shell);
	}
}
