/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:33 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/13 15:57:23 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	size_key_value(char *key, char *value)
{
	int	i;
	int	j;

	i = 0;
	while (key[i] != '\0')
		i++;
	j = 0;
	while (value[j] != '\0')
		j++;
	return (i + j + 1);
}

char	*create_env_entry(const char *key, const char *value)
{
	int		key_len;
	int		val_len;
	int		i;
	int		j;
	char	*entry;

	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	entry = malloc(key_len + val_len + 2);
	if (!entry)
		return (NULL);
	i = 0;
	j = 0;
	while (key[j])
		entry[i++] = key[j++];
	entry[i++] = '=';
	j = 0;
	while (value[j])
		entry[i++] = value[j++];
	entry[i] = '\0';
	return (entry);
}

char	**shell_2_char(t_env *env)
{
	char	**my_env;
	int		size;
	int		i;

	my_env = allocate_env_array(env, &size);
	if (!my_env)
		return (NULL);
	i = 0;
	while (env)
	{
		my_env[i] = create_env_entry(env->key, env->value);
		if (!my_env[i])
		{
			free_env_array(my_env, i);
			g_exit_status = 1;
			return (NULL);
		}
		i++;
		env = env->next;
	}
	my_env[i] = NULL;
	return (my_env);
}

void	ft_execve(char **argv, t_shell *shell)
{
	char	*cmd_path;
	char	**my_env;

	cmd_path = find_path(shell->env, argv[0]);
	if (!cmd_path)
		ft_execve_error_exit(argv[0], 127, ": command not found\n");
	if (access(cmd_path, X_OK) != 0)
	{
		free(cmd_path);
		ft_execve_error_exit(argv[0], 126, ": Permission denied\n");
	}
	my_env = shell_2_char(shell->env);
	if (!my_env)
	{
		free(cmd_path);
		ft_execve_error_exit(argv[0], 1, ": failed to prepare environment\n");
	}
	execve(cmd_path, argv, my_env);
	free(cmd_path);
	write(2, "minishell: execve error\n", 23);
	g_exit_status = 1;
	exit(g_exit_status);
}
