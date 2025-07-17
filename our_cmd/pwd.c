#include "../minishell.h"

void	ft_pwd(char **argv)
{
	char	cwd[4096];

	if (argv[1] != NULL)
	{
		printf("Too many arguments\n");
		g_exit_status = 1;
		return;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exit_status = 0;
	}
	else
	{
		perror("minishell: pwd");
		g_exit_status = 1;
	}
}
