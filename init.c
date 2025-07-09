#include "minishell.h"


t_env	*new_env_node(char *key, char *value)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return NULL;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

t_env	*init_env(char **envp, t_shell *shell)
{
	t_env *head;
	t_env *tail;
	t_env *new;
	char *equal;
	char *key;
	char *value;
	int i;
	int	size;
	int	j;

	i = 0;
	head = NULL;
	tail = NULL;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue;
		}
		key = ft_strndup(envp[i], equal - envp[i]);
		value = ft_strdup(equal + 1);
		if (ft_strncmp(key, "HOME", 4) == 0)
		{
			size = ft_strlen(value);
			shell->home = malloc(sizeof(char) * (size + 1));
			j = 0;
			while (value[j])
			{
				shell->home[j] = value[j];
				j++;
			}
			shell->home[j] = '\0';
		}
		new = new_env_node(key, value);
		if (!new)
			return NULL;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		i++;
	}
	return head;
}

void	init_shell(t_shell *shell, char **env)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->new_path= NULL;
	shell->old_path = NULL;
	shell->home = NULL;
	shell->exit_status = 0;
	shell->env = init_env(env, shell);
}
