#include "minishell.h"

char *ft_strndup(char *line, int n)
{
    char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	while(line[i] && i < n)
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}