#include "minishell.h"

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
	int		size;
	int		j;

	if (ft_strncmp(key, "HOME", 4) == 0)
	{
		size = ft_strlen(value);
		shell->home = malloc(sizeof(char) * (size + 1));
		if (!shell->home)
			return ;
		j = 0;
		while (value[j])
		{
			shell->home[j] = value[j];
			j++;
		}
		shell->home[j] = '\0';
	}
}

t_env	*process_env_var(char *env_entry, t_shell *shell,
		t_env **tail, t_env **head)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*new;

	equal = ft_strchr(env_entry, '=');
	if (!equal)
		return (NULL);
	key = ft_strndup(env_entry, equal - env_entry);
	value = ft_strdup(equal + 1);
	if (ft_strncmp(key, "HOME", 4) == 0)
		set_home_if_needed(key, value, shell);
	new = new_env_node(key, value);
	if (!new)
		return (NULL);
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
		printf("minishell: failed to initialize environment\n");
		exit(1);
	}
}
