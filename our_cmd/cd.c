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

void ft_update_pwd(t_shell *shell)
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
        if (shell->pwd)
        {
            new_pwd = malloc(strlen(shell->pwd) + 3);
            if (!new_pwd)
                return;
            ft_strlcpy(new_pwd, shell->pwd, 4096);
            ft_strlcat(new_pwd, "/..", 4096);
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
            free(shell->pwd);
            shell->pwd = new_pwd;
        }
    }
    ft_faind_and_change("PWD", shell->env, shell->pwd);
    ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
}



// void ft_update_pwd(t_shell *shell)
// {
// 	char cwd[4096];
// 	char *pwd;

// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		pwd = ft_strdup(cwd);
// 		if (shell->pwd)
// 			free(shell->pwd);
// 		shell->pwd = ft_strdup(cwd);
// 	}
// 	else
// 	{
// 		pwd = ft_strdup(shell->pwd);
// 	}

// 	ft_faind_and_change("PWD", shell->env, pwd);
// 	ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
// 	free(pwd);
// }

void	ft_finish(void)
{
	perror("Too MANY Arguments");
	return ;
}

void	ft_cd_more_argument(char *path, t_shell *shell)
{
	char	*pwd;

	shell->len = ft_strlen(path);
	if (strncmp(path, "-", shell->len) == 0)
	{
		pwd = ft_faind_in_env(shell->env, "PWD");
		if (!shell->old_path)
			shell->old_path = pwd;
		else
			shell->old_path = ft_faind_in_env(shell->env, "OLDPWD");
		chdir(shell->old_path);
		shell->temp = pwd;
		ft_faind_and_change("PWD", shell->env, shell->old_path);
		ft_faind_and_change("OLDPWD", shell->env, shell->temp);
		printf("%s\n", ft_faind_in_env(shell->env, "PWD"));
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
	shell->home_chesk = ft_faind_in_env(shell->env, "HOME");
	if (shell->home_chesk)
		shell->home = shell->home_chesk;
	if (argv[1] == NULL)
	{
		if (argv[1] == NULL && shell->home_chesk != NULL)
		{
			shell->old_path = ft_faind_in_env(shell->env, "PWD");
			ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
			ft_faind_and_change("PWD", shell->env, shell->home_chesk);
			chdir(shell->home_chesk);
			return ;
		}
		else
			perror(shell->home_chesk);
	}
	else if (strncmp(&argv[1][0], "~", 1) == 0)
	{
		ft_end_e(shell, argv[1]);
		return ;
	}
	if (ft_check_len_argv(argv) == 0)
		return ;
	ft_cd_more_argument(argv[1], shell);
}
