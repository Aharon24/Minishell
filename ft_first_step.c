#include "minishell.h"

void	ft_first_step(t_s_list *s)
{
	int	i;

	i = 0;
	s->path_env = getenv("PATH");
	s->orignal_path = ft_split(s->path_env, ':');
	while(s->orignal_path[i])
	{
		printf("%s\n",s->orignal_path[i]);
		i++;
	}
	s->arr = ft_split(s->line, ' ');
	if (access(s->arr[0], X_OK) == 0)
		printf("OK\n");
}
