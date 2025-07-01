/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:01:22 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/04 20:12:03 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	if (!dst_ptr && !src_ptr)
		return (NULL);
	if (dst_ptr < src_ptr || dst_ptr >= src_ptr + len)
	{
		while (len--)
			*dst_ptr++ = *src_ptr++;
	}
	else
	{
		while (len--)
			dst_ptr[len] = src_ptr[len];
	}
	return (dst);
}
