#include "../minishell.h"

t_env	*ft_faind_and_change(char *argument, t_env *env, char *new_path)
{
	int		len;
	t_env	*faind;

	faind = env;
	len = ft_strlen(argument);
	while (faind)
	{
		if (ft_strncmp(faind->key, argument, len) == 0)
			break ;
		faind = faind->next;
	}
	faind->value = new_path;
	return (faind);
}

char	*ft_make_path(char *str)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] && str[i] != '/')
		i--;
	new = malloc((i + 1) * sizeof(char ));
	while (str[j] && j <= i)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_faind_in_env(t_env *env, char *argument)
{
	int		len;
	t_env	*faind;

	faind = env;
	len = ft_strlen(argument);
	while (faind)
	{
		if (ft_strncmp(faind->key, argument, len) == 0)
			return (faind->value);
		faind = faind->next;
	}
	return (NULL);
}
