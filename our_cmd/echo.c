#include "../minishell.h"

void	ft_echo(char **argv)
{
	int	i;
	int	j;
	int	check;

	i = 1;
	j = 0;
	check = 1;
	if (!argv[1])
	{
		printf("\n");
		return ;
	}
	if (argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == '\0')
		{
			check = 0;
			i++;
		}
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			printf("%c", argv[i][j]);
			j++;
		}
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (check)
		printf("\n");
}
