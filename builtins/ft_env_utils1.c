/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:26:56 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:26:59 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/execution.h"

void	ft_var_perr(char *str)
{
	printf("minishell: export: `%s' : not a valid identifier\n", str);
	g_vars.exp_f = 1;
}

void	ft_var_free(char **ar, char *temp)
{
	ft_free_ar(ar);
	free(temp);
}

char	*ft_var(char *envp, int *j)
{
	char	*temp;
	char	**ar;
	int		i;

	i = 0;
	if (envp[0] == '=' || envp[0] == '+')
	{
		ft_var_perr(envp);
		return (NULL);
	}
	ar = ft_split(envp, '=');
	temp = ft_strdup2(ar[0], j);
	if (!temp)
	{
		ft_var_free(ar, temp);
		return (NULL);
	}
	if (!ft_check_var(temp) || (*j == 1 && !ar[1] && get_findex(envp) == -1))
	{
		ft_var_perr(ar[0]);
		ft_var_free(ar, temp);
		return (NULL);
	}
	ft_free_ar(ar);
	return (temp);
}

t_env	*ft_cenv(char *envp, int *j)
{
	t_env	*env;
	int		i;
	char	*temp;

	i = get_findex(envp);
	env = malloc(sizeof(t_env));
	temp = ft_var(envp, j);
	if (temp)
		env->first = temp;
	else
	{
		free(temp);
		free(env);
		return (NULL);
	}
	if (i != -1)
		env->second = ft_strdup(envp + i + 1);
	else
		env->second = NULL;
	env->next = NULL;
	return (env);
}

void	ft_free_env(t_env *env)
{
	free(env->first);
	free(env->second);
	free(env);
}
