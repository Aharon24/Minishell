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
	rl_on_new_line();
	rl_replace_line("", 0);
}

char	*read_line_or_exit(void)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell -> ");
	if (!line)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}
