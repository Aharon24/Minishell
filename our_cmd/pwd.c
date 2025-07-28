#include "../minishell.h"

void	ft_pwd(t_shell *shell, char **argv)
{
	char	cwd[4096];

	argv = NULL;
	if(!shell->pwd)
		shell->pwd = ft_faind_in_env(shell->env, "PWD");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		g_exit_status = 0;
	}
	else
	{
		shell->pwd = ft_strjoin(shell->pwd, "..");
		printf("%s\n", shell->pwd);
	}
		
}
