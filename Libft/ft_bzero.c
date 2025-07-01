/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:18:18 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/03 15:59:16 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n != 0)
	{
		*temp = 0;
		temp++;
		n--;
	}
}
/*
#include <stdio.h>
#include <strings.h>

int main()
{
	char str[] = "Hello";
	char str1[] = "Hello";

	ft_bzero(str, 1);
	bzero(str1, 1);

	printf("my version: %s\n", str);
	printf("original: %s\n", str1);
	return (0);
}*/
