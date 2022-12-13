/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:36:03 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:36:05 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

char	*ft_env_path(t_env *env, char *first)
{
	while (env)
	{
		if (ft_strncmp(env->first, first, ft_strlen(env->first)) == 0)
			return (ft_strdup(env->second));
		env = env->next;
	}
	return (NULL);
}

void	ft_free_cd(char *path, char *oldpwd, char *get)
{
	free(path);
	free(oldpwd);
	free(get);
}

void	ft_cd_c_l(char *s, char *path, int *x)
{
	if (!path)
	{
		printf("%s not set\n", s);
		*x = 1;
	}
	else if (chdir(path) == -1)
	{		
		printf("minishell: cd: %s: No such file or directory\n", path);
		*x = 1;
	}
}
