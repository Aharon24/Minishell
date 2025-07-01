/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:40:22 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/07 19:40:25 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr2(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[11];
	int		i;

	i = 0;
	if (ft_nbr2(n, fd))
		return ;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	while (n > 0)
	{
		buffer[i] = '0' + (n % 10);
		n /= 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(fd, &buffer[i], 1);
		i--;
	}
}

/*
#include <stdio.h>

int main()
{
    int a = 100;
    ft_putnbr_fd(a, 1);
    return 0;
}*/