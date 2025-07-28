#include "../minishell.h"

void	ft_printf_export(t_env *export)
{
	t_env	*e;

	e = export;
	while (e)
	{
		if (!e->value && ft_chesk_eqvel(e->key))
			printf("declare -x %s\"\"\n", e->key);
		else if (!e->value && (ft_chesk_eqvel(e->key) == 0))
			printf("declare -x %s\n", e->key);
		else
			printf("declare -x %s=\"%s\"\n", e->key, e->value);
		e = e->next;
	}
}

int	ft_validation_argument(char *arg, int i)
{
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0)
		{
			if (( (ft_isalpha(arg[i])) || arg[i] == '_'))
				i++;
			else
			{
				printf("bash: export: `%s': not a valid identifier\n",arg);
				return (0);
			}
		}
		if ( (ft_isalpha(arg[i]))  || (arg[i] == '_') || (ft_isdigit(arg[i])))
			i++;
		if ( arg[i] == '\0' || arg[i] == '=')
			return (1);
		if (!( (ft_isalnum(arg[i])) || arg[i] == '_' || arg[i] == '='))
		{
			printf("bash: export: `%s': not a valid identifier\n", arg);
			return (0);
		}
	}
	return (1);
}

char	*ft_add_env_key(char *arg)
{
	int		i;
	char	*new;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	new = malloc((i + 1) * sizeof(char));
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		new[i] = arg[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_add_env_value(char *arg)
{
	int		i;
	int		j;
	char	*new;
	char	*link;

	i = 0;
	j = 0;
	new = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	i++;
	link = &arg[i];
	if (arg[i] == '\0')
		return (NULL);
	while (link[j])
		j++;
	new = malloc((j + 1) * sizeof(char));
	j = 0;
	while (link[j])
	{
		new[j] = link[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

int	ft_chesk_eqvel(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '=')
			c++;
	}
	if (c == 1)
		return (c);
	return (0);
}
