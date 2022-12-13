/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:26:48 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:26:50 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/execution.h"

int	get_findex(char *env)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup2(char *el, int *j)
{
	int		i;
	int		size;
	char	*ele;

	i = 0;
	ele = NULL;
	size = ft_strlen(el);
	if (!el)
		return (NULL);
	if (el[size - 1] == '+')
	{
		size--;
		*j = 1;
	}
	ele = malloc(size + 1);
	while (i < size)
	{
		ele[i] = el[i];
		i++;
	}
	ele[i] = '\0';
	return (ele);
}

int	ft_isalnumic(int c)
{
	if ((c > 47 && c < 58) || (c > 64 && c < 91)
		|| (c > 96 && c < 123) || (c == '_'))
		return (1);
	else
		return (0);
}

int	ft_check_var(char *temp)
{
	int	i;

	i = 0;
	if (temp[0] > 47 && temp[0] <= 57)
		return (0);
	while (temp[i])
	{
		if (ft_isalnumic(temp[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_ar(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}
