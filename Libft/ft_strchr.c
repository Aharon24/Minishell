/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:19:39 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/04 21:19:46 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	b;

	b = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == b)
			return ((char *)s);
		s++;
	}
	if (b == '\0')
		return ((char *)s);
	return (NULL);
}
