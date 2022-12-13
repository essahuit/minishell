/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:42:30 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/19 05:42:34 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

int	ft_check_echo(char *str)
{
	int	i;

	if (str[0] != '-' || !str[0])
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo_c2(char **ar, int *flag2, int i)
{
	*flag2 = 1;
	printf("%s", ar[i]);
	if (ar[i + 1])
		printf(" ");
}

void	ft_echo_c(char **ar, int *flag, int *flag2, int i)
{
	int	j;

	if (ft_check_echo(ar[0]) && *flag2 != 1)
	{
		j = 1;
		if (ft_check_echo(ar[i]) == 0)
			j = 0;
		while (ar[i][j])
		{
			if (ar[i][j] != 'n')
			{
				*flag2 = 1;
				printf("%s", ar[i]);
				if (ar[i + 1])
					printf(" ");
				break ;
			}
			else
				*flag = 0;
			j++;
		}
	}
	else
		ft_echo_c2(ar, flag2, i);
}

int	ft_echo(char **ar)
{
	int	i;
	int	flag;
	int	flag2;

	i = 0;
	flag = 1;
	flag2 = 0;
	if (ar)
	{
		while (ar[i])
		{
			ft_echo_c(ar, &flag, &flag2, i);
			i++;
		}
	}
	if (flag == 1)
		printf("\n");
	return (0);
}
