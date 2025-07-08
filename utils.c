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

int	is_exit_command(t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "exit") == 0 && cmd->argv[1] == NULL)
		return (1);
	return (0);
}