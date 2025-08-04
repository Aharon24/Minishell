/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:05:38 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:05:39 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_faind_key_in(t_env *e_e, char *key)
{
	t_env	*e;

	e = e_e;
	while (e)
	{
		if (ft_strcmp(e->key, key) == 0)
			return (1);
		e = e->next;
	}
	return (0);
}

void	ft_add_export_or_env(t_shell *shell, char *arg)
{
	int	i;
	int	n;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	n = ft_faind_and_rm(arg, shell);
	if (n == 2)
		return ;
	if (arg[i] != '=')
	{
		shell->export = ft_add_export(shell->export, arg);
	}
	else if (arg[i] == '=' && arg[i + 1] == '\0')
	{
		shell->export = ft_add_export(shell->export, arg);
		shell->env = ft_add_env(shell->env, arg);
	}
	else
	{
		shell->export = ft_add_export(shell->export, arg);
		shell->env = ft_add_env(shell->env, arg);
	}
}
