#include "../minishell.h"

int	validate_tokens(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	if (!cur)
		return (0);
	if (cur->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	while (cur)
	{
		if (cur->type == TOKEN_PIPE
			&& (!cur->next || cur->next->type == TOKEN_PIPE))
		{
			if (cur->next == NULL)
				ft_putstr_fd("minishell: syntax error "
					"near unexpected token `newline'\n", 2);
			else
				ft_putstr_fd("minishell: syntax error "
					"near unexpected token `|'\n", 2);
			return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

int	extract_key_value(char *env_entry, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(env_entry, '=');
	if (!equal)
		return (0);
	*key = ft_strndup(env_entry, equal - env_entry);
	*value = ft_strdup(equal + 1);
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		return (0);
	}
	return (1);
}

int ft_check_exit_cmd(char **argv)
{
	//int i;
	int number;

	//printf("aaaa\n");
	//i = 0;
	if (argv[1] == NULL)
		return (0);
	else if (ft_ch(argv[1]))
	{
		return (258);
	}
	else if(argv[2])
		return (257);
	number = ft_atoi(argv[1]);
	//printf("11 ->%d\n",number);
	if(number >= 256)
		g_exit_status = number % 256;
	else
		g_exit_status = number;
	return (g_exit_status);

}

int ft_ch(char *arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if( !(arr[i] >= '0' && arr[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}