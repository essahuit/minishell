/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:01:22 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/12 14:52:27 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	get_digits(unsigned int n)
{
	int	i;

	i = 1;
	while (n / 10 > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	power_ten(int expo)
{
	int	res;

	res = 1;
	while (expo > 0)
	{
		res *= 10;
		expo--;
	}
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n1;
	unsigned int	digits;
	char			c;

	if (n < 0)
	{
		n1 = n * (-1);
		ft_putchar_fd('-', fd);
	}
	else
		n1 = n;
	digits = get_digits(n1);
	while (digits > 0)
	{
		c = n1 / power_ten(digits - 1) + '0';
		ft_putchar_fd(c, fd);
		n1 = n1 % power_ten(digits - 1);
		digits--;
	}
}
