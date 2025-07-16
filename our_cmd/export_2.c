#include "../minishell.h"

void	ft_add_export_or_env(t_shell *shell, char *arg)
{
    int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] != '=')
	{
		shell->export = ft_add_export(shell->export, arg);
	}
	else if (arg[i] == '=' && arg[i + 1] == '\0')
	{
		shell->export = ft_add_export(shell->export, arg);
		shell->env =  ft_add_env(shell->env, arg);
	}
	else
	{
		shell->export = ft_add_export(shell->export, arg);
		shell->env = ft_add_env(shell->env, arg);
	}
}

t_env	*ft_add_export(t_env *export, char *arg)
{
	t_env	*start;
	char	*key;
	char	*value;
    int     i;
    
    i = 0;
    printf("LINE  %s\n",arg);
    value = NULL;
	key = NULL;
    if (!export || !export->next)
		return (NULL);
	start = export;
    while (start->next)
		start = start->next;
	key = ft_ket_string(arg);
    while(arg[i] && arg[i] != '=')
        i++;
    if (arg[i + 1] == '\0')
        value  = ft_strdup("");
	else
		value = ft_value_string(arg);
	printf("key in export %s \n",key);
	start->next = new_env_node(key,value);
	printf("key %s value %s",start->next->key,start->next->value);
	return (export);
}

t_env *ft_add_env(t_env *env, char *arg)
{
	t_env	*start;
	char	*key;
	char	*value;
    int     i;

	i = 0;
    value = NULL;
	key = NULL;
    if (!env || !env->next)
		return (NULL);
	start = env;
    while (start->next)
		start = start->next;
	key = ft_ket_string(arg);
    while(arg[i] && arg[i] != '=')
        i++;
    if (arg[i + 1] == '\0')
        value  = ft_strdup("");
	else
		value = ft_value_string(arg);
	start->next = new_env_node(key,value);
	return (env);
}
char	*ft_value_string(char *arg)
{
	int	i;
	int j; 
	char *new;
	char *link;

	new = NULL;
	i = 0;
	j = 0;
	new = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	i++;
	link = &arg[i];
	if (arg[i] == '\0')
		return (NULL);
	while(link[j])
		j++;
	new = malloc( (j + 1) * sizeof(char));
	j = 0;
	while (link[j])
	{
		new[j] = link[j];
		j++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_ket_string(char *arg)
{
    int i;
    char *new;

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