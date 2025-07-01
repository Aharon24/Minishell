/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:15:45 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/06 14:15:46 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;
	size_t	j;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	s1 = (char *)malloc((len + 1) * sizeof(char));
	if (!s1)
		return (NULL);
	i = start;
	j = 0;
	while (j < len)
	{
		s1[j] = s[i];
		i++;
		j++;
	}
	s1[j] = '\0';
	return (s1);
}

/*#include <stdio.h>

int	main()
{
	char *s = "hello world";
	printf("%s\n", ft_substr(s, 2, 3));
	return (0);
}*/