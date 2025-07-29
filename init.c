#include "minishell.h"

int	init_remove_data(t_expand_data *d, char *input)
{
	d->i = 0;
	d->j = 0;
	d->sq = 0;
	d->dq = 0;
	d->len = ft_strlen(input);
	d->res = malloc(d->len * 100 + 1);
	if (!d->res)
		return (0);
	ft_memset(d->res, 0, d->len * 100 + 1);
	return (1);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	set_home_if_needed(const char *key, const char *value, t_shell *shell)
{
	if (ft_strncmp(key, "HOME", 4) == 0)
	{
		if (shell->home)
			free(shell->home);
		shell->home = ft_strdup(value);
	}
}

t_env	*process_env_var(char *env_entry, t_shell *shell,
			t_env **tail, t_env **head)
{
	char	*key;
	char	*value;
	t_env	*new;

	if (!extract_key_value(env_entry, &key, &value))
		return (NULL);
	set_home_if_needed(key, value, shell);
	new = new_env_node(key, value);
	if (!new)
	{
		free(key);
		free(value);
		return (NULL);
	}
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	return (new);
}

t_env	*init_env(char **envp, t_shell *shell)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new = process_env_var(envp[i], shell, &tail, &head);
		if (new)
			tail = new;
		i++;
	}
	return (head);
}

void	init_shell(t_shell *shell, char **env)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->old_path = NULL;
	shell->home = NULL;
	shell->export = NULL;
	shell->pwd = NULL;
	shell->check_exit = 0;
	shell->env = init_env(env, shell);
	if (!shell->env)
	{
		write(2, "minishell: failed to initialize environment\n", 44);
		exit(1);
	}
}
