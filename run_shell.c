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
// 	int i = 0;

// 	while(cmd)
// 	{
// 		i = 0;
// 		while (cmd->argv[i])
// 		{
// 			printf("%s",cmd->argv[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		cmd = cmd->next;
// 	}
// }

void	run_shell(t_shell *shell)
{
	t_command *cmd;

	while (1)
	{
		shell->line = readline("minishell-> ");
		if (!shell->line)
			break;
		if (shell->line[0] == '\0')
		{
			free(shell->line);
			continue;
		}
		if (tokenize(shell) == -1)
			printf("Ошибка токенизации\n");
		cmd = split_cmd(shell->tokens);
		check_arrow(cmd);
		print_cmd(cmd);
		cleanup_loop(shell);
	}
}
