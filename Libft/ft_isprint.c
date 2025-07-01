/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:30:40 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/03 13:53:08 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main()
{
	int c = 45;
	printf("my version: %d\n", ft_isprint(c));
	printf("original: %d\n", isprint(c));
	return (0);
}*/
