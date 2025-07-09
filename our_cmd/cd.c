#include "../minishell.h"


void ft_end_e(t_shell *shell, char *path)
{
	if (path[0] == '~' && path[1] == '\0')
	{
		shell->old_path = ft_faind_in_env(shell->env,"PWD");
		ft_faind_and_change("OLDPWD",shell->env,shell->old_path);
		ft_faind_and_change("PWD", shell->env, shell->home);
		chdir(shell->home);
		return ;
	}
	else if (path[0] == '~' && path[1])
	{
		ft_check_t(shell,path);
	}
}
void ft_update_pwd(t_shell *shell)
{
	char *pwd;
	char cwd[4096];
	pwd = ft_faind_in_env(shell->env,"PWD");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		pwd = ft_strdup(cwd);
	ft_faind_and_change("PWD",shell->env,pwd);
	ft_faind_and_change("OLDPWD",shell->env,shell->old_path);
}

void	ft_finish(void)
{
	perror("Too MANY Arguments");
	return ;
}

void	ft_cd_more_argument(char *path, t_shell *shell)
{
	int		len;
	char	*pwd;

	len = 0;
	len = ft_strlen(path);
	if (strncmp(path, "-", len) == 0)
	{
		pwd = ft_faind_in_env(shell->env, "PWD");
		if(!shell->old_path)
			shell->old_path = pwd;
		else
			shell->old_path = ft_faind_in_env(shell->env,"OLDPWD");
		chdir(shell->old_path);
		shell->temp  = pwd;
		ft_faind_and_change("PWD",shell->env,shell->old_path);
		ft_faind_and_change("OLDPWD",shell->env,shell->temp);
		printf("%s\n",ft_faind_in_env(shell->env,"PWD"));
		return ;
	}
	if (chdir(path) == 0)
	{
		pwd = ft_faind_in_env(shell->env, "PWD");
		shell->old_path = pwd;
		ft_update_pwd(shell);
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
			shell->old_path = ft_faind_in_env(shell->env,"PWD");
			ft_faind_and_change("OLDPWD",shell->env,shell->old_path);
			ft_faind_and_change("PWD", shell->env, home);
			chdir(home);
			return ;
		}
		else
			perror(home);
	}
	else if(strncmp(&argv[1][0], "~",1) == 0)
	{
		ft_end_e(shell,argv[1]);
		return ;
	}
	while (argv[i])
		i++;
	if (i > 2)
		ft_finish();
	ft_cd_more_argument(argv[1], shell);
}
