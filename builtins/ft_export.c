/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:41:49 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/19 05:41:52 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

int	ft_export_len(t_exp **exp)
{
	int	i;

	i = 0;
	while (exp[i])
		i++;
	return (i);
}

void	ft_export_add(t_env **env, char **ar)
{
	int	n;

	n = 0;
	while (ar[n])
	{
		ft_add_env(env, ar[n]);
		n++;
	}
}

void	ft_export_sort(t_exp **exp)
{
	t_exp	*temp;
	int		n;
	int		i;
	int		j;

	i = ft_export_len(exp);
	n = 0;
	while (n < i - 1)
	{
		j = 0;
		while (n < i - j - 1)
		{
			if (ft_strncmp(exp[j]->first, exp[j + 1]->first,
					len_calc(exp[j]->first, exp[j + 1]->first)) > 0)
			{
				temp = exp[j];
				exp[j] = exp[j + 1];
				exp[j + 1] = temp;
			}
			j++;
		}
		n++;
	}
}

int	ft_export(char **ar, t_env **env)
{
	t_exp	**exp;
	int		flag;

	flag = 1;
	exp = conv_exp(*env);
	if (ar)
		flag = ft_export_l(ar);
	if (ft_strlen2(ar) == 0 || flag == -1)
	{
		ft_export_sort(exp);
		ft_export_p(exp);
	}
	else
		ft_export_add(env, ar);
	ft_free_exp(exp);
	if (g_vars.exp_f == 1)
		return (1);
	return (0);
}
