/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:18:18 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/08/08 19:19:08 by ahapetro         ###   ########.fr       */
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
