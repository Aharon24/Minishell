/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:14:13 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/04 22:14:15 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	b;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	b = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == b)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
