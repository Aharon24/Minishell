/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:07:03 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:07:04 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_check_exit_cmd(char **argv)
{
	int	number;

	number = 0;
	if (argv[1] == NULL)
		return (0);
	else if (ft_ch(argv[1]))
	{
		return (258);
	}
	else if (argv[2])
		return (257);
	number = ft_atoi(argv[1]);
	if (number >= 256)
		g_exit_status = number % 256;
	else
		g_exit_status = number;
	return (g_exit_status);
}

int	ft_ch(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!(arr[i] >= '0' && arr[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
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

void	free_env_array(char **env_arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(env_arr[i]);
		i++;
	}
	free(env_arr);
}
