#include "../minishell.h"

void	ft_pwd(char **argv)
{
	char	cwd[4096];

	if (argv[1] != NULL)
	{
		printf("To many arguments\n");
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}
