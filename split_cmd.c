#include "minishell.h"

void	new_cmd_init(t_command *new_cmd)
{
	new_cmd->argv = NULL;
	new_cmd->pip = 0;
	new_cmd->redirects = NULL;
	new_cmd->next = NULL;
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

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd_init(new_cmd);
	size = size_(tokens);
	new_cmd->argv = malloc(sizeof(char *) * (size + 1));
	if (!new_cmd->argv)
	{
		free(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

int	process_redirect(t_token **tokens, t_command *new_cmd, t_shell *shell)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (-1);
	redir->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		exit(2);
	}
	redir->filename = remove_quotes_and_expand((*tokens)->value, shell->env);
	if (!redir->filename)
	{
		free(redir);
		return (-1);
	}
	redir->next = NULL;
	add_redirect(&new_cmd->redirects, redir);
	*tokens = (*tokens)->next;
	return (0);
}

int	fill_argv_and_redirects(t_token **tokens,
	t_command *new_cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			new_cmd->argv[i] = remove_quotes_and_expand((*tokens)->value,
					shell->env);
			if (!new_cmd->argv[i])
				return (-1);
			i++;
			*tokens = (*tokens)->next;
		}
		else if ((*tokens)->type == TOKEN_REDIRECT_IN
			|| (*tokens)->type == TOKEN_HEREDOC
			|| (*tokens)->type == TOKEN_REDIRECT_OUT
			|| (*tokens)->type == TOKEN_REDIRECT_APPEND)
		{
			if (process_redirect(tokens, new_cmd, shell) == -1)
				return (-1);
		}
		else
			*tokens = (*tokens)->next;
	}
	new_cmd->argv[i] = NULL;
	return (0);
}

t_command	*split_cmd(t_token *tokens, t_shell *shell)
{
	t_command	*cmd_head;
	t_command	*new_cmd;

	cmd_head = NULL;
	while (tokens)
	{
		new_cmd = allocate_new_command(tokens);
		if (!new_cmd)
		{
			free_cmd(cmd_head);
			return (NULL);
		}
		if (fill_argv_and_redirects(&tokens, new_cmd, shell) == -1)
		{
			free_command(new_cmd);
			free_cmd(cmd_head);
			return (NULL);
		}
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			new_cmd->pip = 1;
			tokens = tokens->next;
		}
		add_new_cmd(&cmd_head, new_cmd);
	}
	return (cmd_head);
}

// t_command	*split_cmd(t_token *tokens, t_shell *shell)
// {
// 	t_command	*cmd_head;
// 	t_command	*new_cmd;
// 	t_redirect	*redir;
// 	int			i;
// 	int			size;

// 	cmd_head = NULL;
// 	while (tokens)
// 	{
// 		new_cmd = malloc(sizeof(t_command));
// 		if (!new_cmd)
// 			return (NULL);
// 		new_cmd_init(new_cmd);
// 		size = size_(tokens);
// 		new_cmd->argv = malloc(sizeof(char *) * (size + 1));
// 		if (!new_cmd->argv)
// 			return (NULL);
// 		i = 0;
// 		while (tokens && tokens->type != TOKEN_PIPE)
// 		{
// 			if (tokens->type == TOKEN_WORD)
// 			{
// 				new_cmd->argv[i++] = remove_quotes_and_expand
//										(tokens->value, shell->env);;
// 				tokens = tokens->next;
// 			}
// 			else if (tokens->type == TOKEN_REDIRECT_IN ||
// 					tokens->type == TOKEN_HEREDOC ||
// 					tokens->type == TOKEN_REDIRECT_OUT ||
// 					tokens->type == TOKEN_REDIRECT_APPEND)
// 			{
// 				redir = malloc(sizeof(t_redirect));
// 				if (!redir)
// 					return (NULL);
// 				redir->type = tokens->type;
// 				tokens = tokens->next;
// 				if (!tokens || tokens->type != TOKEN_WORD)
// 				{
// 					ft_putstr_fd("syntax error near unexpected
//								token `newline'\n", 2);
// 					exit(2);
// 				}
// 				redir->filename = remove_quotes_and_expand(tokens->value,
//												shell->env);;
// 				redir->next = NULL;
// 				add_redirect(&new_cmd->redirects, redir);
// 				tokens = tokens->next;
// 			}
// 			else
// 				tokens = tokens->next;
// 		}
// 		new_cmd->argv[i] = NULL;
// 		if (tokens && tokens->type == TOKEN_PIPE)
// 		{
// 			new_cmd->pip = 1;
// 			tokens = tokens->next;
// 		}
// 		add_new_cmd(&cmd_head, new_cmd);
// 	}
// 	return (cmd_head);
// }
