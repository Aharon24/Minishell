#include "minishell.h"

void	free_tokens(t_token **head)
{
	t_token *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->value);
		free(tmp);
	}
}
void cleanup_loop(t_shell *shell)
{
	if (shell->line)
		free(shell->line);
	shell->line = NULL;

	free_tokens(&(shell->tokens));
	shell->tokens = NULL;
}

void	free_redirects(t_redirect *redir)
{
	t_redirect *tmp;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->filename);
		free(tmp);
	}
}

void free_command(t_command *cmd)
{
	int i;

	if (!cmd)
		return;

	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}

	free_redirects(cmd->redirects);
	free(cmd);
}

void free_cmd(t_command *cmd)
{
	t_command *tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_command(cmd);
		cmd = tmp;
	}
}

void	free_env(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	shell->env = NULL;

	if (shell->tokens)
		free_tokens(&(shell->tokens));
	shell->tokens = NULL;

	if (shell->home)
		free(shell->home);
	shell->home = NULL;

	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = NULL;
}
