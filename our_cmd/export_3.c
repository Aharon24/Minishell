#include "../minishell.h"

int ft_faind_key_in(t_env *e_e, char *key)
{
	t_env *e;

	e = e_e;
	while (e)
	{
		if (ft_strcmp(e->key, key) == 0)
			return (1);
		e = e->next;
	}
	return (0);
}