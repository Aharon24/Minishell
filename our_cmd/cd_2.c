
#include "../minishell.h"

int	ft_check_t(t_shell *shell, char *path)
{
	int check;
	int i;
	char *new;
	char *pwd;

	check = 0;
	printf("%s",shell->home);
	i = 0;
	if (path[i] == '~')
		path++;
	new = malloc ((ft_strlen(path) + 1) * sizeof(char));
	while (path[i])
	{
		new[i] = path[i];
		i++;
	}
	new[i] = '\0';
	if (!shell->home)
		shell->home = ft_faind_in_env(shell->env, "HOME");
	pwd = ft_strjoin(shell->home,new);
	if(chdir(pwd) == 0)
	{
		///
		return (1);
	return (0);
}