#include "minishell.h"

void new_cmd_init(t_command *new_cmd)
{
	new_cmd->argv = NULL;
	new_cmd->pip = 0;
	new_cmd->redirects = NULL;
	new_cmd->next = NULL;
}

int size_(t_token *tokens)
{
	int size = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			size++;
		tokens = tokens->next;
	}
	return size;
}

t_command *split_cmd(t_token *tokens)
{
	t_command *cmd_head = NULL;
	t_command *new_cmd;
	t_redirect *redir;
	int i;
	int size;

	while (tokens)
	{
		new_cmd = malloc(sizeof(t_command));
		if (!new_cmd)
			return NULL;
		new_cmd_init(new_cmd);
		size = size_(tokens);
		new_cmd->argv = malloc(sizeof(char *) * (size + 1));
		if (!new_cmd->argv)
			return NULL;
		i = 0;
		while (tokens && tokens->type != TOKEN_PIPE)
		{
			if (tokens->type == TOKEN_WORD)
			{
				new_cmd->argv[i++] = ft_strdup(tokens->value);
				tokens = tokens->next;
			}
			else if (tokens->type == TOKEN_REDIRECT_IN ||
					tokens->type == TOKEN_HEREDOC ||
					tokens->type == TOKEN_REDIRECT_OUT ||
					tokens->type == TOKEN_REDIRECT_APPEND)
			{
				redir = malloc(sizeof(t_redirect));
				if (!redir)
					return NULL;
				redir->type = tokens->type;
				tokens = tokens->next;
				if (!tokens || tokens->type != TOKEN_WORD)
				{
					ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
					exit(2);
				}
				redir->filename = ft_strdup(tokens->value);
				redir->next = NULL;
				add_redirect(&new_cmd->redirects, redir);
				tokens = tokens->next;
			}
			else
				tokens = tokens->next;
		}
		new_cmd->argv[i] = NULL;
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			new_cmd->pip = 1;
			tokens = tokens->next;
		}
		add_new_cmd(&cmd_head, new_cmd);
	}
	return cmd_head;
}
