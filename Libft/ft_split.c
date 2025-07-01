/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:30:03 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/07 13:30:06 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			count++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (count);
}

static int	len_world(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] == c)
		i++;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

static char	*get_word(char	**str, char c)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((len_world(*str, c) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (**str != '\0' && **str == c)
		(*str)++;
	while (**str != '\0' && **str != c)
	{
		word[i] = **str;
		(*str)++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_split(char **res, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(res[j]);
		j++;
	}
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		word_c;
	char	*s1;
	int		i;

	s1 = (char *)s;
	i = 0;
	word_c = word_count(s1, c);
	res = (char **)malloc((word_c + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < word_c)
	{
		res[i] = get_word(&(s1), c);
		if (res[i] == NULL)
		{
			free_split(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
