/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:04:58 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:04:59 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_one(char **new_pwd, t_shell *shell)
{
	*new_pwd = malloc(ft_strlen(shell->pwd) + 3);
	if (!*new_pwd)
		return ;
	ft_strlcpy(*new_pwd, shell->pwd, ft_strlen(shell->pwd) + 1);
	ft_strlcat(*new_pwd, "/.", ft_strlen(shell->pwd) + 3);
}

void	ft_two(char **new_pwd, t_shell *shell)
{
	*new_pwd = malloc(ft_strlen(shell->pwd) + 4);
	if (!*new_pwd)
		return ;
	ft_strlcpy(*new_pwd, shell->pwd, ft_strlen(shell->pwd) + 1);
	ft_strlcat(*new_pwd, "/..", ft_strlen(shell->pwd) + 4);
}

void	ft_dash(char **new_pwd, t_shell *shell)
{
	if (shell->old_path)
		*new_pwd = ft_strdup(shell->old_path);
	else
		*new_pwd = ft_strdup("");
}

void	ft_tilda(char **new_pwd, t_shell *shell)
{
	if (shell->home)
		*new_pwd = ft_strdup(shell->home);
	else
		*new_pwd = ft_strdup("");
}

void	ft_relative(char **new_pwd, t_shell *shell, char *path)
{
	size_t	len;

	len = ft_strlen(shell->pwd) + ft_strlen(path) + 2;
	*new_pwd = malloc(len);
	if (!*new_pwd)
		return ;
	ft_strlcpy(*new_pwd, shell->pwd, ft_strlen(shell->pwd) + 1);
	ft_strlcat(*new_pwd, "/", len);
	ft_strlcat(*new_pwd, path, len);
}
