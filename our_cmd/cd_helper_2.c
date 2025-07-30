#include "../minishell.h"

void	ft_resolve_pwd(char **new_pwd, t_shell *shell, char *path)
{
	if (ft_strcmp(path, ".") == 0)
		ft_one(new_pwd, shell);
	else if (ft_strcmp(path, "..") == 0)
		ft_two(new_pwd, shell);
	else if (path[0] == '/')
		*new_pwd = ft_strdup(path);
	else if (ft_strcmp(path, "-") == 0)
		ft_dash(new_pwd, shell);
	else if (path[0] == '~')
		ft_tilda(new_pwd, shell);
	else
		ft_relative(new_pwd, shell, path);
}

void	ft_handle_cd_dash(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_faind_in_env(shell->env, "PWD");
	oldpwd = ft_faind_in_env(shell->env, "OLDPWD");
	if (!shell->old_path)
		shell->old_path = ft_strdup(pwd);
	else
	{
		free(shell->old_path);
		shell->old_path = ft_strdup(oldpwd);
	}
	if (chdir(shell->old_path) != 0)
	{
		perror(shell->old_path);
		return ;
	}
	free(shell->temp);
	shell->temp = ft_strdup(pwd);
	ft_faind_and_change("PWD", shell->env, shell->old_path);
	ft_faind_and_change("OLDPWD", shell->env, shell->temp);
	printf("%s\n", ft_faind_in_env(shell->env, "PWD"));
}

void	ft_handle_cd_home(t_shell *shell)
{
	char	*pwd;

	if (shell->home != NULL)
	{
		pwd = ft_faind_in_env(shell->env, "PWD");
		if (shell->old_path)
			free(shell->old_path);
		shell->old_path = ft_strdup(pwd);
		ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
		ft_faind_and_change("PWD", shell->env, shell->home);
		chdir(shell->home);
	}
	else
	{
		write(2, "minishell: HOME not set\n", 24);
	}
}
