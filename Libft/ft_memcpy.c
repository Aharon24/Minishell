/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:24:37 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/03 15:58:48 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *)dst;
	temp2 = (unsigned char *)src;
	i = 0;
	if (!temp1 && !temp2)
		return (NULL);
	while (i < n)
	{
		temp1[i] = temp2[i];
		i++;
	}
	return ((void *)temp1);
}
