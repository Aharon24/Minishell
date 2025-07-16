#include "../minishell.h"

void	ft_printf_export(t_env *export)
{
	t_env *e;

	e = export;
	while (e)
	{
		if(!e->value)
			printf("declare -x %s\n",e->key);
		else 
			printf("declare -x %s=%s\n", e->key, e->value);
		e = e->next;
	}
}

int ft_validation_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if(i == 0)
		{
			if ((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' &&arg[i] <= 'Z')  || arg[i] == '_' )
				i++;
			else
			{
				printf("1\n");
				return (0);
			}
		}
		if((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z')  || arg[i] == '_' || (arg[i] >= '0' && arg[i] <= '9') || arg[i] == '=')
			i++;
		if( arg[i] == '\0')
			return (1);
		// else
		// {
		// 	printf("2\n");
		// 	return (0);
		// }
	}
	return (1);
}



////////////////////// add_env_key;
////////////////////// add_env_value;








// void ft_maybe_in_env_or_exporrt(t_shell *t_shell, t_env *env)
// {

// }
