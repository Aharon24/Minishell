#include "../minishell.h"

int	ft_check_n_flag(char **argv, int *i)
{
	int	j;

	if (!argv[*i])
		return (1);
	if (argv[*i][0] == '-')
	{
		j = 1;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] == '\0')
		{
			(*i)++;
			return (0);
		}
	}
	return (1);
}

void	ft_echo(char **argv)
{
	int	i;
	int	j;
	int	print_newline;

	i = 1;
	if (!argv[1])
	{
		write(1, "\n", 1); // stdout
		return ;
	}
	print_newline = ft_check_n_flag(argv, &i);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			write(1, &argv[i][j], 1); // stdout
			j++;
		}
		if (argv[i + 1] != NULL)
			write(1, " ", 1); // stdout
		i++;
	}
	if (print_newline)
		write(1, "\n", 1); // stdout
}


