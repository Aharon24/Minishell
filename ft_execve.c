#include "minishell.h"

void	ft_execve(char **argv, t_shell *shell)
{
	char	*cmd_path;

	cmd_path = find_path(shell->env,argv[0]);
	execve(cmd_path,argv,NULL);
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
		{
			//free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	//free_split(paths);
	return (NULL);
}

char	*find_path(t_env *s, char *cmd)
{
	char	**paths;
	char	*path_env;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = ft_faind_in_env(s,"PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (find_path_helper(paths, cmd));
}