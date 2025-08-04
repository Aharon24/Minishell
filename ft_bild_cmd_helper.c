/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bild_cmd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:25 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:06:26 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_cd(char **argv, t_shell *shell)
{
	ft_cd(argv, shell);
	return (1);
}

int	ft_exec_unset(char **argv, t_shell *shell)
{
	ft_unset(argv, shell);
	return (1);
}

int	ft_exec_export(char **argv, t_shell *shell)
{
	ft_export(shell, argv);
	return (1);
}

int	ft_exec_exit(char **argv)
{
	int	status;

	status = ft_check_exit_cmd(argv);
	if (status == 257)
		write(2, "exit: too many arguments\n", 26);
	else if (status == 258)
	{
		write(2, "exit: numeric argument required\n", 33);
		exit(2);
	}
	else
		exit(status);
	return (1);
}
