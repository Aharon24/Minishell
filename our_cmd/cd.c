/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:07 by ahapetro          #+#    #+#             */
/*   Updated: 2025/09/04 18:12:23 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_end_e(t_shell *shell, char *path)
{
	if (path[0] == '~' && path[1] == '\0')
	{
		if (shell->old_path)
			free(shell->old_path);
		shell->old_path = strdup(ft_faind_in_env(shell->env, "PWD"));
		ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
		ft_faind_and_change("PWD", shell->env, shell->home);
		if (chdir(shell->home) == 0)
			g_exit_status = 0;
		else
		{
			perror(shell->home);
			g_exit_status = 1;
		}
		return ;
	}
	else if (path[0] == '~' && path[1])
	{
		if (path[0] == '~')
			path++;
		ft_check_t(shell, path);
	}
}

void	ft_update_pwd(t_shell *shell, char *path)
{
	char	cwd[4096];
	char	*new_pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (shell->pwd)
			free(shell->pwd);
		shell->pwd = ft_strdup(cwd);
	}
	else
	{
		if (!shell->pwd)
			return ;
		ft_resolve_pwd(&new_pwd, shell, path);
		free(shell->pwd);
		shell->pwd = new_pwd;
		printf("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n");
	}
	ft_faind_and_change("PWD", shell->env, shell->pwd);
	ft_faind_and_change("OLDPWD", shell->env, shell->old_path);
}

void	ft_finish(void)
{
	printf("minishell: cd: too many arguments\n");
	return ;
}

void	ft_cd_more_argument(char *path, t_shell *shell)
{
	char	*pwd;

	shell->len = ft_strlen(path);
	if (strncmp(path, "-", shell->len) == 0)
	{
		if (!shell->old_path)
		{
			g_exit_status = 1;
			return ;
		}
		ft_handle_cd_dash(shell);
		return ;
	}
	if (chdir(path) == 0)
	{
		g_exit_status = 0;
		pwd = ft_faind_in_env(shell->env, "PWD");
		if (shell->old_path)
			free(shell->old_path);
		shell->old_path = ft_strdup(pwd);
		ft_update_pwd(shell, path);
	}
	else
		ft_qsan_hing_tox(path);
}

void	ft_cd(char **argv, t_shell *shell)
{
	shell->home_chesk = ft_faind_in_env(shell->env, "HOME");
	if (shell->home_chesk)
	{
		if (shell->home)
			free(shell->home);
		shell->home = ft_strdup(shell->home_chesk);
	}
	if (argv[1] == NULL)
	{
		ft_handle_cd_home(shell);
		g_exit_status = 0;
		return ;
	}
	else if (argv[1][0] == '~')
	{
		ft_end_e(shell, argv[1]);
		return ;
	}
	if ((argv) == 0)
	{
		g_exit_status = 1;
		return ;
	}
	ft_cd_more_argument(argv[1], shell);
}
