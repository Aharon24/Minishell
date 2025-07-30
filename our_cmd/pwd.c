#include "../minishell.h"

// void	ft_pwd(t_shell *shell)
// {
// 	char	cwd[4096];

// 	if(!shell->pwd)
// 		shell->pwd = ft_faind_in_env(shell->env, "PWD");
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		printf("%s\n", cwd);
// 		g_exit_status = 0;
// 	}
// }

void	ft_pwd(t_shell *shell)
{
	char	cwd[4096];

	if (!shell->pwd)
		shell->pwd = ft_faind_in_env(shell->env, "PWD");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exit_status = 0;
	}
	else
	{
		if (shell->pwd)
		{
			printf("%s\n", shell->pwd);
			g_exit_status = 0;
		}
		else
		{
			perror("pwd");
			g_exit_status = 1;
		}
	}
}
