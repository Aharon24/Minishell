#include "../minishell.h"

void	ft_pwd(char **argv)
{
	char	cwd[4096];

	if (argv[1] != NULL)
	{
		printf("Too many arguments\n");
		g_exit_status = 1;
		ft_free_arr(argv);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exit_status = 0;
	}
	// else if(!cwd)
	// {
	// 	printf("--->%s\n", cwd);
	// }
	else
	{
		perror("minishell: pwd");
		ft_free_arr(argv);
		g_exit_status = 1;
	}
}
