#include "minishell.h"

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

int	copy_var_value(char *res, int j, char *input, int *i, t_env *env)
{
	int		start;
	char	*name;
	char	*val;

	start = ++(*i);
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	name = ft_substr(input, start, *i - start);
	val = get_env_value(name, env);
	ft_strlcpy(res + j, val, ft_strlen(val) + 1);
	j += ft_strlen(val);
	free(name);
	free(val);
	return (j);
}

char	*remove_quotes_and_expand(char *input, t_env *env)
{
	int		i;
	int		j;
	int		sq;
	int		dq;
	int		k;
	int		len;
	char	*res;
	int		o;
	char 	*exit_code_str;


	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	len = ft_strlen(input);
	res = malloc(len * 100 + 1);
	if (!res)
		return (NULL);
	k = 0;
	while (k < len * 2 + 1)
		res[k++] = 0;
	while (input[i])
	{
		if (input[i] == '\'' && dq == 0)
		{
			sq = !sq;
			i++;
		}
		else if (input[i] == '"' && sq == 0)
		{
			dq = !dq;
			i++;
		}
		else if (input[i] == '$' && input[i + 1] == '?' && sq == 0)
		{
			exit_code_str = ft_itoa(g_exit_status);
			o = 0;
			while (exit_code_str[o])
				res[j++] = exit_code_str[o++];
			free(exit_code_str);
			i += 2;
		}
		else if (input[i] == '$' && sq == 0 &&
			(ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
			j = copy_var_value(res, j, input, &i, env);
		else
		{
			res[j] = input[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strndup(char *line, int n)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	while (line[i] && i < n)
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

