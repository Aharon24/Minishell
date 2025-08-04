/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:07:04 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:07:05 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_exit_cmd(char **argv)
{
	int		i;
	long	exit_code;
	char	*endptr;

	if (!argv[1])
		return (0);
	exit_code = strtol(argv[1], &endptr, 10);
	if (*endptr != '\0')
		return (258);
	i = 1;
	while (argv[i])
		i++;
	if (i > 2)
		return (257);
	return ((int)(exit_code & 0xFF));
}

void	print_str(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
}

char	*get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

// int	copy_var_value(char *res, int j, char *input, int *i, t_env *env)
// {
// 	int		start;
// 	char	*name;
// 	char	*val;

// 	start = ++(*i);
// 	while (ft_isalnum(input[*i]) || input[*i] == '_')
// 		(*i)++;
// 	name = ft_substr(input, start, *i - start);
// 	val = get_env_value(name, env);
// 	ft_strlcpy(res + j, val, ft_strlen(val) + 1);
// 	j += ft_strlen(val);
// 	free(name);
// 	free(val);
// 	return (j);
// }

int	copy_var_value(char *res, int j, t_expand_ctx *ctx)
{
	int		start;
	char	*name;
	char	*val;

	start = ++(*ctx->i);
	while (ft_isalnum(ctx->input[*ctx->i]) || ctx->input[*ctx->i] == '_')
		(*ctx->i)++;
	name = ft_substr(ctx->input, start, *ctx->i - start);
	val = get_env_value(name, ctx->env);
	ft_strlcpy(res + j, val, ft_strlen(val) + 1);
	j += ft_strlen(val);
	free(name);
	free(val);
	return (j);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
