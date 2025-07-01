/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:34:43 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/07 18:34:46 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s1;
	int		len;
	char	*res;
	int		i;

	s1 = (char *)s;
	len = ft_strlen(s1);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = f(i, s1[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
