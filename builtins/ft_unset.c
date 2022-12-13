/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:41:19 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/19 05:41:23 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/execution.h"

void	ft_unset_c(char *str, int *x)
{
	*x = 1;
	printf("minishell: unset: `%s' : not a valid identifier\n", str);
}

void	ft_unset_free(t_env *temp)
{
	free(temp->first);
	free(temp->second);
	free(temp);
}

void	ft_unset_c2(char **ar, t_env *env)
{
	t_env	*temp;
	int		i;

	while (env)
	{
		i = 0;
		while (ar[i])
		{
			temp = env->next;
			if (temp && ft_strcmp(temp->first, ar[i]) == 0)
			{
				env->next = temp->next;
				ft_unset_free(temp);
			}
			i++;
		}
		env = env->next;
	}
}

int	ft_unset(t_env **env_t, char **ar)
{
	t_env	*temp;
	int		i;
	int		x;

	x = 0;
	if (ar)
	{
		i = 0;
		while (ar[i])
		{
			if (!ft_check_var(ar[i]))
				ft_unset_c(ar[i], &x);
			else if (*env_t && ft_strcmp((*env_t)->first, ar[i]) == 0)
			{
				temp = *env_t;
				*env_t = (*env_t)->next;
				ft_unset_free(temp);
			}
			i++;
		}
		ft_unset_c2(ar, *env_t);
		if (x == 1)
			return (1);
	}
	return (0);
}
