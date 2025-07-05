#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

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