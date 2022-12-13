/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:55:50 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:19:35 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

void	ft_perror(int i, char *s)
{
	if (i == 0)
		printf("minishell: %s: command not found\n", s);
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", s);
	else if (i == 2)
		printf("fork error");
	else if (i == 3)
		printf("pipe error");
	else if (i == 4)
		printf(" ");
	else if (i == 5)
		printf(" ");
	else if (i == 6)
		printf(" ");
	exit(127);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(to_find) == 0 && ft_strlen(str) != 0)
		return (str);
	if (ft_strlen(str) == ft_strlen(to_find))
	{
		if (ft_strcmp(str, to_find) == 0)
			return (str);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[j + i] == to_find[j] && to_find[j] != '\0')
				j++;
			if (j == ft_strlen(to_find) && (str[0] == to_find[0]))
				return (&str[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_path(char **envp)
{
	int		i;
	char	*a;

	i = 0;
	a = "PATH=";
	while (envp[i])
	{
		if (ft_strncmp(envp[i], a, 5) == 0)
			return (envp[i]);
		i++;
	}
	return ("");
}

void	ft_free_two(char **ar)
{
	size_t	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}
