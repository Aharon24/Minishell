#include "minishell.h"

// int	fill_argv_and_redirects(t_token **tokens,
// 	t_command *new_cmd, t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	while (*tokens && (*tokens)->type != TOKEN_PIPE)
// 	{
// 		if ((*tokens)->type == TOKEN_WORD)
// 		{
// 			new_cmd->argv[i]
// 				= remove_quotes_and_expand((*tokens)->value, shell->env);
// 			if (!new_cmd->argv[i])
// 			{
// 				ft_free_arr(new_cmd->argv);
// 				return (-1);
// 			}
// 			i++;
// 			*tokens = (*tokens)->next;
// 		}
// 		else if ((*tokens)->type == TOKEN_REDIRECT_IN
// 			|| (*tokens)->type == TOKEN_HEREDOC
// 			|| (*tokens)->type == TOKEN_REDIRECT_OUT
// 			|| (*tokens)->type == TOKEN_REDIRECT_APPEND)
// 		{
// 			if (process_redirect(tokens, new_cmd, shell) == -1)
// 			{
// 				ft_free_arr(new_cmd->argv);
// 				return (-1);
// 			}
// 		}
// 		else
// 		{
// 			*tokens = (*tokens)->next;
// 		}
// 	}
// 	new_cmd->argv[i] = NULL;
// 	return (0);
// }

void	new_cmd_init(t_command *new_cmd)
{
	new_cmd->argv = NULL;
	new_cmd->pip = 0;
	new_cmd->redirects = NULL;
	new_cmd->next = NULL;
	new_cmd->syntax_error = 0;
	new_cmd->argc = 0;
}

int	size_(t_token *tokens)
{
	int	size;

	size = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			size++;
		tokens = tokens->next;
	}
	return (size);
}

t_command	*allocate_new_command(t_token *tokens)
{
	int			size;
	t_command	*new_cmd;
	int			i;

	size = size_(tokens);
	new_cmd = malloc(sizeof(t_command));
	i = 0;
	if (!new_cmd)
		return (NULL);
	new_cmd_init(new_cmd);
	new_cmd->argv = malloc(sizeof(char *) * (size + 1));
	if (!new_cmd->argv)
	{
		free(new_cmd);
		return (NULL);
	}
	while (i <= size)
	{
		new_cmd->argv[i] = NULL;
		i++;
	}
	return (new_cmd);
}

int	parse_one_command(t_token **tokens, t_command **cmd_head, t_shell *shell)
{
	t_command	*new_cmd;

	new_cmd = allocate_new_command(*tokens);
	if (!new_cmd)
		return (-1);
	if (fill_argv_and_redirects(tokens, new_cmd, shell) == -1)
	{
		free_command(new_cmd);
		return (-1);
	}
	if (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		new_cmd->pip = 1;
		*tokens = (*tokens)->next;
	}
	add_new_cmd(cmd_head, new_cmd);
	return (0);
}

t_command	*split_cmd(t_token *tokens, t_shell *shell)
{
	t_command	*cmd_head;

	cmd_head = NULL;
	while (tokens)
	{
		if (parse_one_command(&tokens, &cmd_head, shell) == -1)
		{
			free_cmd(cmd_head);
			return (NULL);
		}
	}
	return (cmd_head);
}
