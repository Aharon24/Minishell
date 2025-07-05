#include "../minishell.h"

void	ft_env(t_shell *shell)
{
	t_env *env = shell->env;

	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}