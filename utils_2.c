#include "../minishell.h"

int ft_chesk_exit_cmd(char **argv)
{
	int i;
	int number;

	printf("aaaa\n");
	i = 0;
	if (argv[1] == NULL)
		return (0);
	if(argv[2])
		return (2);
	if (ft_ch(argv))
		exit(2);
	number = ft_atoi(argv[1]);
	if(number > 255)
		g_exit_status = number % 255;
	else
		g_exit_status = number;
	return (g_exit_status);

}

int ft_ch(char **arr)
{
	int i;
	int j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while(arr[i][j])
		{
			if( !(arr[i][j] >= '0' && arr[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}