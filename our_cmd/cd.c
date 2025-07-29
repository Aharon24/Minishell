#include "../minishell.h"


void	ft_end_e(t_shell *shell, char *path)
{
	if (path[0] == '~' && path[1] == '\0')
	{
		shell->old_path = ft_faind_in_env(shell->env, "PWD");
		ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
		ft_faind_and_change("PWD", shell->env, shell->home);
		chdir(shell->home);
		return ;
	}
	else if (path[0] == '~' && path[1])
	{
		if (path[0] == '~')
			path++;
		ft_check_t(shell, path);
		return ;
	}
}

void ft_update_pwd(t_shell *shell, char *path)
{
    char cwd[4096];
    char *new_pwd;

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (shell->pwd)
            free(shell->pwd);
        shell->pwd = ft_strdup(cwd);
    }
    else
    {
        if (!shell->pwd)
            return;

        if (ft_strcmp(path, ".") == 0)
        {
        }
        else if (ft_strcmp(path, "..") == 0)
        {
            new_pwd = malloc(ft_strlen(shell->pwd) + 4);
            if (!new_pwd)
                return;
            ft_strlcpy(new_pwd, shell->pwd, ft_strlen(shell->pwd) + 1);
            ft_strlcat(new_pwd, "/..", ft_strlen(shell->pwd) + 4);
            free(shell->pwd);
            shell->pwd = new_pwd;
        }
        else if (path[0] == '/')
        {
            free(shell->pwd);
            shell->pwd = ft_strdup(path);
        }
        else if (ft_strcmp(path, "-") == 0)
        {
            free(shell->pwd);
            shell->pwd = ft_strdup(shell->old_path ? shell->old_path : "");
        }
        else if (path[0] == '~')
        {
            free(shell->pwd);
            shell->pwd = ft_strdup(shell->home ? shell->home : "");
        }
        else
        {
            new_pwd = malloc(ft_strlen(shell->pwd) + ft_strlen(path) + 2);
            if (!new_pwd)
                return;
            ft_strlcpy(new_pwd, shell->pwd, ft_strlen(shell->pwd) + 1);
            ft_strlcat(new_pwd, "/", ft_strlen(shell->pwd) + ft_strlen(path) + 2);
            ft_strlcat(new_pwd, path, ft_strlen(shell->pwd) + ft_strlen(path) + 2);
            free(shell->pwd);
            shell->pwd = new_pwd;
        }
        printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
    }
    ft_faind_and_change("PWD", shell->env, shell->pwd);
    ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
}


void	ft_finish(void)
{
	perror("Too MANY Arguments");
	return ;
}

void	ft_cd_more_argument(char *path, t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	shell->len = ft_strlen(path);
	if (strncmp(path, "-", shell->len) == 0)
	{
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
			return;
		}
		free(shell->temp);
		shell->temp = ft_strdup(pwd);
		ft_faind_and_change("PWD", shell->env, shell->old_path);
		ft_faind_and_change("OLDPWD", shell->env, shell->temp);
		printf("%s\n", ft_faind_in_env(shell->env, "PWD"));
		return ;
	}
	if (chdir(path) == 0)
	{
		pwd = ft_faind_in_env(shell->env, "PWD");
		free(shell->old_path);
		shell->old_path = ft_strdup(pwd);
		ft_update_pwd(shell, path);
	}
	else
		perror(path);
}

void	ft_cd(char **argv, t_shell *shell)
{
	char *pwd;

	shell->home_chesk = ft_faind_in_env(shell->env, "HOME");
	if (shell->home_chesk)
	{
		if (shell->home)
			free(shell->home);
		shell->home = ft_strdup(shell->home_chesk);
	}

	if (argv[1] == NULL)
	{
		if (shell->home != NULL)
		{
			pwd = ft_faind_in_env(shell->env, "PWD");
			if (shell->old_path)
				free(shell->old_path);
			shell->old_path = ft_strdup(pwd);
			ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
			ft_faind_and_change("PWD", shell->env, shell->home);
			chdir(shell->home);
			return ;
		}
		else
		{
			write(2, "minishell: HOME not set\n", 24);
			return ;
		}
	}
	else if (argv[1][0] == '~')
	{
		ft_end_e(shell, argv[1]);
		return ;
	}
	if (ft_check_len_argv(argv) == 0)
		return ;
	ft_cd_more_argument(argv[1], shell);
}
