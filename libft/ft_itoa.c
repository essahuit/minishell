/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:25:15 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/14 20:21:40 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	get_digits(long num)
{
	int		i;

	i = 1;
	if (num < 0)
	{
		num = -num;
		i++;
	}
	while ((num / 10) != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static int	ten_pow(int expo)
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

static void	fill_(long num, char *ptr, int i)
{
	int	digits;

	digits = get_digits(num);
	while (digits > 0)
	{
		ptr[i] = num / ten_pow(digits - 1) + '0';
		num = num % ten_pow(digits - 1);
		i++;
		digits--;
	}
	ptr[i] = '\0';
}

char	*ft_itoa(int n)
{
	long			num;
	char			*ptr;
	int				i;

	i = 0;
	num = n;
	ptr = malloc(sizeof(char) * (get_digits(num) + 1));
	if (ptr == NULL)
		return (NULL);
	if (num < 0)
	{
		ptr[0] = '-';
		num = -num;
		i++;
	}
	fill_(num, ptr, i);
	return (ptr);
}
