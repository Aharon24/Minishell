/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:04:44 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/08 12:04:46 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	b;
	char			*last;

	b = (unsigned char)c;
	last = NULL;
	while (*s)
	{
		if ((unsigned char)*s == b)
			last = (char *)s;
		s++;
	}
	if (b == '\0')
		return ((char *)s);
	return (last);
}

/*#include <stdio.h>

int	main()
{
	char *s = "hello world";
	printf("%s\n", ft_strrchr(s, 'o'));
	return (0);

}*/