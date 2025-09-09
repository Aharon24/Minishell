/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:32 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/13 18:42:19 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_env_array(t_env *env, int *out_size)
{
	char	**my_env;
	int		size;

	size = size_env(env);
	my_env = malloc((size + 1) * sizeof(char *));
	if (!my_env)
	{
		g_exit_status = 1;
		return (NULL);
	}
	*out_size = size;
	return (my_env);
}

char	*find_path_helper(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			break ;
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(t_env *s, char *cmd)
{
	char	**paths;
	char	*path_env;
	char	*result;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path_env = ft_faind_in_env(s, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = find_path_helper(paths, cmd);
	ft_free_arr(paths);
	return (result);
}

void	ft_execve_error_exit(char *cmd, int code, char *msg)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	g_exit_status = code;
	exit(g_exit_status);
}

int	check_command_permission(t_shell *shell, char *cmd)
{
	char	*cmd_path;

	cmd_path = find_path(shell->env, cmd);
	if (cmd_path == NULL)
	{
		free(cmd_path);
		return (127);
	}
	if (access(cmd_path, X_OK) != 0 && access(cmd_path, F_OK) == 0)
	{
		free(cmd_path);
		return (126);
	}
	free(cmd_path);
	return (0);
}
