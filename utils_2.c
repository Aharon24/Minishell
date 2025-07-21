#include "../minishell.h"

int ft_check_exit_cmd(char **argv)
{
	int i;
	int number;

	//printf("aaaa\n");
	i = 0;
	if (argv[1] == NULL)
		return (0);
	else if (ft_ch(argv[1]))
	{
		printf("%s numeric argument required\n",argv[1]);
		return (2);
	}
	else if(argv[2])
		return (257);

	number = ft_atoi(argv[1]);
	//printf("11 ->%d\n",number);
	if(number >= 256)
		g_exit_status = number % 256;
	else
		g_exit_status = number;
	return (g_exit_status);

}

int ft_ch(char *arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if( !(arr[i] >= '0' && arr[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}