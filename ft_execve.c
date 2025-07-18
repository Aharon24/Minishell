#include "minishell.h"

int		size_env(t_env *env)
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

char	**shell_2_char(t_env *env)
{
	char	**my_env;
	int		size;
	int		i;

	i = 0;
	size = size_env(env);
	my_env = malloc((size + 1) * sizeof(char *));
	if (!my_env)
	{
		g_exit_status = 1;
		return (NULL);
	}
	while (env)
	{
		int		key_len;
		int		val_len;
		int		j;
		int		t;

		t = 0;
		j = 0;
		key_len = 0;
		val_len = 0;
		while (env->key[key_len])
			key_len++;
		while (env->value[val_len])
			val_len++;
		my_env[i] = malloc(key_len + val_len + 2);
		if (!my_env[i])
		{
			g_exit_status = 1;
			return (NULL);
		}
		while (j < key_len)
			my_env[i][t++] = env->key[j++];
		my_env[i][t++] = '=';
		j = 0;
		while (j < val_len)
			my_env[i][t++] = env->value[j++];

		my_env[i][t] = '\0';

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
	int		ev;

	ev = 0;
	my_env = NULL;
	cmd_path = find_path(shell->env,argv[0]);
	if (!cmd_path)
	{
		printf("minishell: %s: command not found\n", argv[0]);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	my_env = shell_2_char(shell->env);
	if (!my_env)
	{
		printf("minishell: failed to prepare environment\n");
		g_exit_status = 1;
		//free(cmd_path);
		exit(g_exit_status);
	}
	if ((ft_strcmp("cat", argv[0]) == 0) && argv[1] == NULL)
		return ;
	execve(cmd_path, argv, my_env);
	perror("minishell: execve");
	g_exit_status = 126;
	exit(g_exit_status);
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