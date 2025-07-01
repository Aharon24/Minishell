/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:54:21 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/03 13:54:36 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)ptr;
	while (len != 0)
	{
		*temp = (unsigned char)value;
		temp++;
		len--;
	}
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char str[] = "123";
	char str1[] = "123";
	printf("my version: %s\n", ft_memset(str, 'A', 3));
	printf("original: %s\n", memset(str1, 'A', 3));
	return (0);
}*/
