#include "../minishell.h"

void	ft_finish(void)
{
	perror("Too MANY Arguments");
	return ;
}

void	ft_cd_more_argument(char *path, t_shell *shell)
{
	char	*new_pwd1;
	char	*new_pwd2;
	int		len;
	char	*pwd;
	char	*env_get;

	len = 0;
	len = ft_strlen(path);
	env_get = ft_faind_in_env(shell->env, "PWD");
	new_pwd1 = ft_strjoin("/", path);
	new_pwd2 = ft_strjoin(env_get, new_pwd1);
	if (chdir(new_pwd2) == 0)
	{
		pwd = ft_faind_in_env(shell->env, "PWD");
		pwd = new_pwd2;
		ft_faind_and_change("PWD", shell->env, new_pwd2);
		printf("\nWork\n");
	}
	else
		perror(path);
}

void	ft_cd(char **argv, t_shell *shell)
{
	char	*home;
	int		i;

	i = 0;
	home = ft_faind_in_env(shell->env, "HOME");
	if (home)
		shell->home = home;
	if (argv[1] == NULL)
	{
		if (argv[1] == NULL && home != NULL)
		{
			ft_faind_and_change("PWD", shell->env, home);
			chdir(home);
			return ;
		}
		else
			perror(home);
	}
	while (argv[i])
		i++;
	if (i > 2)
		ft_finish();
	ft_cd_more_argument(argv[1], shell);
}
