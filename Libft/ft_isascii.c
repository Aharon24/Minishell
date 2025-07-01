/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:12:46 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/03 12:24:07 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	return (1);
}
/*
#include <stdio.h>
#include <ctype.h>

int main()
{
	int c = -1;
	printf("my version: %d\n", ft_isascii(c));
	printf("original: %d\n", isascii(c));
	return (0);
}*/
