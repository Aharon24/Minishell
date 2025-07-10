#include "../minishell.h"

void	ft_check_t(t_shell *shell, char *path)
{
	int		i;
	char	*new;
	char	*pwd;
	char	*get_pwd;

	i = 0;
	new = malloc ((ft_strlen(path) + 1) * sizeof(char));
	while (path[i])
	{
		new[i] = path[i];
		i++;
	}
	new[i] = '\0';
	if (!shell->home)
		shell->home = ft_faind_in_env(shell->env, "HOME");
	pwd = ft_strjoin(shell->home, new);
	if (chdir(pwd) == 0)
	{
		get_pwd = ft_faind_in_env(shell->env, "PWD");
		ft_faind_and_change("OLDPWD", shell->env, get_pwd);
		ft_faind_and_change("PWD", shell->env, pwd);
	}
	else
		perror("No");
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
		return (0);
	}
	return (1);
}
