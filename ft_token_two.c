#include "minishell.h"

char	**ft_arr_env_join_slesh(char **arr)
{
	char	*a;
	int		i;

	i = 0;
	a = ft_strdup("/");
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		arr[i] = ft_strjoin(arr[i], a);
		i++;
	}
	free(a);
	return (arr);
}

void	ft_tray_acsses(char **arr_env, t_token *chek)
{
	int		i;
	char	*arr;

	arr = NULL;
	i = 0;
	arr_env = ft_arr_env_join_slesh(arr_env);
	while (arr_env[i])
	{
		arr = ft_strjoin(arr_env[i], chek->value);
		if (access(arr, X_OK) == 0)
			printf("\ngoooood\n");
		i++;
	}
}

void	ft_run_program(t_token *chek, t_line *line)
{
	line->get_env = getenv("PATH");
	line->arr_get_env = ft_split(line->get_env, ':');
	ft_tray_acsses(line->arr_get_env, chek);
   	// printf("\n---END\n");
    //printf("%s",chek->value);
}

void	ft_token_check_and_do(t_token *chek, int flag, t_line *line)
{
	if (chek->type == TOKEN_WORD && flag == 1)
		ft_run_program(chek, line);
}
