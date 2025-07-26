#include "../minishell.h"

void	unset_env(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp("_", key) == 0)
			return ;
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_env(&(shell->env), argv[i]);
		unset_env(&(shell->export), argv[i]);
		i++;
	}
}

int	ft_faind_and_rm(char *arg, t_shell *shell)
{
	char	*get;
	char	*key;

	key = NULL;
	get = NULL;
	key = ft_ket_string(arg);
	get = ft_faind_in_env(shell->export, key);
	if (!get)
		unset_env(&(shell->export), key);
	if ((ft_strcmp(key, arg) == 0) && get)
		return (2);
	return (1);
}

int	ft_chesk__(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
