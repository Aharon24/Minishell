/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:47:51 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/08 13:56:11 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*arr;

	arr = (t_list *)malloc(sizeof(t_list));
	if (!arr)
		return (NULL);
	arr->content = content;
	arr->next = NULL;
	return (arr);
}
