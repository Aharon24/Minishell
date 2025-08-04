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
	g_exit_status = 0;
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

	if (access(cmd, X_OK) == 0)
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
