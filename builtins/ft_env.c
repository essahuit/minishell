/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:42:47 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/19 05:42:49 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/execution.h"

t_env	*ft_last_env(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

char	*ft_env_dup_temp(t_env *env, t_env *e_env)
{
	char	*temp;

	if (env->second)
		temp = ft_strjoin(env->second, e_env->second);
	else
		temp = ft_strdup(e_env->second);
	free(env->second);
	return (temp);
}

int	ft_env_dup(t_env *env, t_env *e_env, int j)
{
	char	*temp;
	int		x;

	while (env)
	{
		x = ft_strncmp(env->first, e_env->first, ft_strlen(e_env->first) + 1);
		if (j == 1 && (x == 0))
		{
			temp = ft_env_dup_temp(env, e_env);
			env->second = temp;
			ft_free_env(e_env);
		}
		else if (x == 0 && e_env->second)
		{
			free(env->second);
			env->second = ft_strdup(e_env->second);
			ft_free_env(e_env);
		}
		else if (x == 0)
			ft_free_env(e_env);
		if (x == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_add_env(t_env **env, char *envp)
{
	t_env	*el;
	t_env	*e_env;
	int		j;

	j = 0;
	e_env = ft_cenv(envp, &j);
	if (!e_env)
		return ;
	if (!*env)
	{
		*env = e_env;
		return ;
	}
	if (ft_env_dup(*env, e_env, j) == 1)
		return ;
	el = ft_last_env(*env);
	el->next = e_env;
}

int	ft_env(char **env, char **ar)
{
	int	i;

	i = 0;
	if (ft_strlen2(ar) > 0)
	{
		printf("env: %s: No such file or directory\n", ar[0]);
		return (127);
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
