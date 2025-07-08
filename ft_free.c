#include "minishell.h"

void	clear_tokens(t_token **head)
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

	clear_tokens(&(shell->tokens));
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
void	free_cmd(t_command *cmd)
{
	t_command *tmp;
	int i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;

		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
				free(tmp->argv[i++]);
			free(tmp->argv);
		}
		free_redirects(tmp->redirects);
		free(tmp);
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

	if (shell->new_path)
		free(shell->new_path);
	shell->new_path = NULL;

	if (shell->home)
		free(shell->home);
	shell->home = NULL;

	if (shell->pwd)
		free(shell->pwd);
	shell->pwd = NULL;
}
