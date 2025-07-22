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
		unset_env(&(shell->export),argv[i]);
		i++;
	}
}

char	*ft_ket_string_rm(char *arg)
{
	int		i;
	char	*new;
	int		j;

	i = 0;
	j = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	new = malloc((i + 1) * sizeof(char));
	while (arg[j] && j <= i - 1)
	{
		new[j] = arg[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}


void ft_faind_and_rm(char *arg, t_shell *shell)
{
	char *key;

	key = ft_ket_string_rm(arg);
	printf("-----------%s\n",key);
	unset_env(&(shell->export),key);
}
