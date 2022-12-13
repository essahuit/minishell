/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:20:07 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:20:09 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

t_env	*init_envt(char	**envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		ft_add_env(&env, envp[i]);
		i++;
	}
	return (env);
}

int	ft_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**conv_env(t_env *env)
{
	char	**e_env;
	int		size;
	int		i;
	char	*temp;

	i = 0;
	size = ft_size_env(env);
	e_env = malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		temp = ft_strjoin(env->first, "=");
		if (env->second != NULL)
		{
			e_env[i] = ft_strjoin(temp, env->second);
			i++;
		}
		free(temp);
		env = env->next;
	}
	e_env[i] = NULL;
	return (e_env);
}

char	**ft_set_env(char **env, t_env *env_t)
{
	int		i;
	char	**env_e;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
	env_e = conv_env(env_t);
	return (env_e);
}

void	set_vars(t_env *env_t)
{
	char	*home;

	free(g_vars.home);
	free(g_vars.pwd);
	home = getenv("HOME");
	while (env_t)
	{
		if (ft_strncmp(env_t->first, "PWD", len_calc(env_t->first, "PWD")) == 0)
		{
			if (env_t->second)
				g_vars.pwd = ft_strdup(env_t->second);
		}
		env_t = env_t->next;
	}
	if (home != NULL)
		g_vars.home = ft_strdup(home);
	else
		g_vars.home = ft_strdup("rah ma ghat segfaultihach");
}
