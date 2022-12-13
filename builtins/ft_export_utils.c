/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:27:08 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:27:09 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

t_exp	**conv_exp(t_env *env)
{
	t_exp	**exp;
	int		size;
	int		i;

	size = ft_size_env(env);
	exp = malloc((size + 1) * sizeof(t_exp *));
	i = 0;
	while (env)
	{
		exp[i] = malloc(sizeof(t_exp));
		exp[i]->first = ft_strdup(env->first);
		exp[i]->second = ft_strdup(env->second);
		i++;
		env = env->next;
	}
	exp[i] = NULL;
	return (exp);
}

t_env	*ft_cenv_e(char **ar)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->first = ft_strdup(ar[0]);
	env->second = ft_strdup(ar[1]);
	env->next = NULL;
	return (env);
}

void	ft_free_exp(t_exp **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		free(exp[i]->first);
		free(exp[i]->second);
		free(exp[i]);
		i++;
	}
	free(exp);
}

void	ft_export_p(t_exp **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		printf("declare -x %s", exp[i]->first);
		if (exp[i]->second)
		{
			printf("=");
			printf("\"%s\"\n", exp[i]->second);
		}
		else
			printf("\n");
		i++;
	}
}

int	ft_export_l(char **ar)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	while (ar[i])
	{
		if (ft_strlen(ar[i]))
		{
			flag = 0;
			break ;
		}
		i++;
	}
	return (flag);
}
