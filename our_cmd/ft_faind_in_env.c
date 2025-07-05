#include "../minishell.h"

char	*ft_faind_in_env(t_env *env, char *argument)
{
	int i;
	int len;
	t_env *faind;

	faind = env;
	len = ft_strlen(argument);
	i = 0;
	
	while (faind)
	{
		if(ft_strncmp(faind->key,argument,len) == 0)
			return (faind->value);
		faind = faind->next;
	}
	return (NULL);
}
