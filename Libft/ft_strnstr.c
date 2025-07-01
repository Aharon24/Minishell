/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:56:38 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/04 22:56:47 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	if (!*needle)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] != '\0' && i + needle_len <= len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int	main()
{
	const char *big = "";
    const char *small = "";
    
    char *result = ft_strnstr(big, small, 20);
    if (result)
        printf("Найдено: %s\n", result);
    else
        printf("Не найдено\n");

    return 0;
}*/