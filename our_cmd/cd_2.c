/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:04:05 by ahapetro          #+#    #+#             */
/*   Updated: 2025/09/04 18:02:42 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_else(void)
{
	perror("No");
	g_exit_status = 1;
}

int	ft_chlp(void)
{
	g_exit_status = 1;
	return (0);
}

int	artur(t_shell **shell, char **get_pwd, char **new)
{
	char	*pwd;

	if (!(*shell)->home)
	{
		free(*new);
		g_exit_status = 1;
		return (0);
	}
	pwd = ft_strjoin((*shell)->home, *new);
	free(*new);
	if (!pwd)
		return (ft_chlp());
	if (chdir(pwd) == 0)
	{
		*get_pwd = ft_faind_in_env((*shell)->env, "PWD");
		ft_faind_and_change("OLDPWD", (*shell)->env, *get_pwd);
		ft_faind_and_change("PWD", (*shell)->env, pwd);
		g_exit_status = 0;
	}
	else
		ft_else();
	free(pwd);
	return (1);
}

void	ft_check_t(t_shell *shell, char *path)
{
	int		i;
	char	*new;
	char	*get_pwd;

	i = 0;
	new = NULL;
	new = malloc(ft_strlen(path) + 1);
	if (!new)
	{
		g_exit_status = 1;
		return ;
	}
	while (path[i])
	{
		new[i] = path[i];
		i++;
	}
	new[i] = '\0';
	if (!shell->home)
		shell->home = ft_faind_in_env(shell->env, "HOME");
	if (!artur(&shell, &get_pwd, &new))
		return ;
}

int	ft_check_len_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_finish();
		g_exit_status = 1;
		return (0);
	}
	return (1);
}
