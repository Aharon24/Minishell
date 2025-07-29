#include "minishell.h"

// char	*remove_quotes_and_expand(char *input, t_env *env)
// {
// 	int		i;
// 	int		j;
// 	int		sq;
// 	int		dq;
// 	int		k;
// 	int		len;
// 	char	*res;
// 	int		o;
// 	char 	*exit_code_str;

// 	i = 0;
// 	j = 0;
// 	sq = 0;
// 	dq = 0;
// 	len = ft_strlen(input);
// 	res = malloc(len * 100 + 1);
// 	if (!res)
// 		return (NULL);
// 	k = 0;
// 	while (k < len * 2 + 1)
// 		res[k++] = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' && dq == 0)
// 		{
// 			sq = !sq;
// 			i++;
// 		}
// 		else if (input[i] == '"' && sq == 0)
// 		{
// 			dq = !dq;
// 			i++;
// 		}
// 		else if (input[i] == '$' && input[i + 1] == '?' && sq == 0)
// 		{
// 			exit_code_str = ft_itoa(g_exit_status);
// 			o = 0;
// 			while (exit_code_str[o])
// 				res[j++] = exit_code_str[o++];
// 			free(exit_code_str);
// 			i += 2;
// 		}
// 		else if (input[i] == '$' && sq == 0 &&
// 			(ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
// 			j = copy_var_value(res, j, input, &i, env);
// 		else
// 		{
// 			res[j] = input[i];
// 			j++;
// 			i++;
// 		}
// 	}
// 	res[j] = '\0';
// 	return (res);
// }

int	handle_dollar_case(char *input, t_expand_data *d,
	t_env *env, int *i)
{
	char	*exit_str;
	int		o;

	if (input[*i + 1] == '?')
	{
		exit_str = ft_itoa(g_exit_status);
		o = 0;
		while (exit_str[o])
			d->res[d->j++] = exit_str[o++];
		free(exit_str);
		*i += 2;
	}
	else
		d->j = copy_var_value(d->res, d->j, input, i, env);
	return (0);
}

int	handle_quotes(char *input, t_expand_data *d)
{
	if (input[d->i] == '\'' && d->dq == 0)
	{
		d->sq = !d->sq;
		d->i++;
		return (1);
	}
	if (input[d->i] == '"' && d->sq == 0)
	{
		d->dq = !d->dq;
		d->i++;
		return (1);
	}
	return (0);
}

void	handle_dollar_or_char(char *input, t_expand_data *d, t_env *env)
{
	if (input[d->i] == '$' && d->sq == 0)
	{
		if (input[d->i + 1] == '?'
			|| ft_isalpha(input[d->i + 1]) || input[d->i + 1] == '_')
			handle_dollar_case(input, d, env, &d->i);
		else
			d->res[d->j++] = input[d->i++];
	}
	else
		d->res[d->j++] = input[d->i++];
}

void	copy_without_quotes_and_expand(char *input,
	t_expand_data *d, t_env *env)
{
	while (input[d->i])
	{
		if (!handle_quotes(input, d))
			handle_dollar_or_char(input, d, env);
	}
}

char	*remove_quotes_and_expand(char *input, t_env *env)
{
	t_expand_data	d;

	if (!init_remove_data(&d, input))
		return (NULL);
	copy_without_quotes_and_expand(input, &d, env);
	d.res[d.j] = '\0';
	return (d.res);
}
