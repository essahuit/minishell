/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:40:39 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/19 05:52:55 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

void	ft_atoii_arg(int k, const char *str, unsigned long long n)
{
	if (k > 19 || n > 9223372036854775807)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", str);
		set(&g_vars.exit, 255);
		exit(255);
	}
}

int	ft_atoii(const char *str)
{
	size_t				i;
	size_t				k;
	int					sign;
	unsigned long long	n;

	i = 0;
	n = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	k = i;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i++] - '0');
	k = i - k;
	ft_atoii_arg(k, str, n);
	n = n * sign;
	return ((int)n);
}

int	ft_check_exit(char *a)
{
	int	i;

	i = 0;
	if (!a)
		return (1);
	while (a[i])
	{
		if (!ft_isdigit(a[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **ar)
{
	int		x;
	char	*a;

	if (!ar)
		a = NULL;
	else if (ft_strlen2(ar) >= 2)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	else
		a = ar[0];
	if (ft_check_exit(a))
	{
		x = ft_atoii(a) % 256;
		printf("exit\n");
	}
	else
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", a);
		x = 255;
	}
	exit(x);
	return (x);
}
