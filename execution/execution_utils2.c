/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:19:49 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:19:53 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

char	*ft_checkaccess(char *cmd, char **cm)
{
	if (access(cmd, X_OK) == 0)
	{
		ft_free_two(cm);
		return (cmd);
	}
	return (NULL);
}

char	*ft_free_one(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*ft_access(char *cmd, char **arpath)
{
	char	*ncmd;
	char	*ocmd;
	char	**cm;
	int		i;

	init_vars_access(&i, &ocmd);
	cm = ft_split1(cmd, ' ');
	if (ft_checkaccess(cmd, cm))
		return (cmd);
	ft_free_two(cm);
	if (ft_strchr(cmd, '/') == NULL)
	{
		ocmd = ft_strjoin("/", cmd);
		while (arpath[++i])
		{
			ncmd = ft_strjoin(arpath[i], ocmd);
			if (access(ncmd, X_OK) == 0)
			{
				free(ocmd);
				return (ncmd);
			}
			ft_free_one(ncmd, arpath[i]);
		}
	}
	return (ft_free_one(ocmd, NULL));
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;

	i = 0;
	if (!s1)
		return (NULL);
	s = malloc(ft_strlen(s1) + 1);
	if (!s)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

size_t	ft_len(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			j++;
		while (s[i] != c && s[i])
			i++;
	}
	return (j);
}
