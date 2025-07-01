/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:21:23 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/07 17:21:25 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	count;

	if (n >= 0 && n <= 9)
		return (1);
	count = 0;
	if (n < 0)
	{
		count ++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	len = len - 1;
	while (n != 0)
	{
		res[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (res);
}

/*#include <stdio.h>

int main()
{
    int n = 0;
    printf("%s", ft_itoa(n));
    return (0);
}*/