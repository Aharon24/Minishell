/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:27:55 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/03 12:24:23 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*#include <stdio.h>
#include <ctype.h>

int main()
{
	int c = 'a';
	printf("my version: %d\n", ft_isalnum(c));
	printf("original: %d\n", isalnum(c));
	return (0);
}*/
