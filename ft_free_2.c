/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:36 by ahapetro          #+#    #+#             */
/*   Updated: 2025/09/08 19:58:38 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_tokens(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->value);
		free(tmp);
	}
}

int	check_command_and_permissions(t_shell *shell,
		t_command *cmd, pid_t *pid_out)
{
	int	handle;
	int	check;
	int	prev_fd;

	prev_fd = -1;
	if (handle_empty_command(cmd, &prev_fd, pid_out))
		return (1);
	handle = handle_builtin_command(cmd, shell, pid_out);
	if (handle == 1)
		return (1);
	else if (handle == -1)
		return (-1);
	check = check_command_permission(shell, cmd->argv[0]);
	if (check == 126)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": Permission denied\n", 21);
		g_exit_status = 126;
		*pid_out = -1;
		return (1);
	}
	return (0);
}

void	er_case(t_command *cmd)
{
	if (cmd->pip)
		exit(127);
	write(2, "minishell: ", 11);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": command not found\n", 20);
	exit(127);
}
