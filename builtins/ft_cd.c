/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:41:32 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/19 05:41:36 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

char	*ft_cd_c(char **ar, t_env *env, int *x)
{
	char	*path;
	char	*s;

	s = NULL;
	if (ft_strncmp(ar[0], "-", len_calc(ar[0], "-")) == 0)
	{
		s = ft_strdup("OLDPWD");
		path = ft_env_path(env, "OLDPWD");
	}
	else if (ft_strncmp(ar[0], "~", len_calc(ar[0], "~")) == 0)
		path = ft_strdup(g_vars.home);
	else
	{
		s = ft_strdup(ar[0]);
		path = ft_strdup(ar[0]);
	}
	ft_cd_c_l(s, path, x);
	free(s);
	return (path);
}

void	ft_cd_l(char *str, int *x)
{
	if (str)
		chdir(str);
	else
	{
		printf("HOME not set\n");
		*x = 1;
	}
}

void	ft_cd_x(t_env *env, int *x, char *oldpwd)
{
	char	*pwd;
	char	*s;

	pwd = getcwd(NULL, 1024);
	if (oldpwd)
		ft_add_env(&env, oldpwd);
	if (pwd)
	{
		s = ft_strjoin("PWD=", pwd);
		ft_add_env(&env, s);
		free(s);
	}
	else
	{
		printf("cd: error retrieving current directory: \
		getcwd:cannot access parent directories: No such file or directory\n");
		*x = 0;
	}
	free(pwd);
}

int	ft_cd(char **ar, t_env *env)
{
	char	*path;
	char	*oldpwd;
	int		x;
	char	*get;

	x = 0;
	get = getcwd(NULL, 1024);
	path = NULL;
	oldpwd = NULL;
	if (get)
		oldpwd = ft_strjoin("OLDPWD=", get);
	if (!ar)
	{
		path = ft_env_path(env, "HOME");
		ft_cd_l(path, &x);
	}
	else
		path = ft_cd_c(ar, env, &x);
	ft_cd_x(env, &x, oldpwd);
	set_vars(env);
	ft_free_cd(path, oldpwd, get);
	if (x == 1)
		return (1);
	return (0);
}
