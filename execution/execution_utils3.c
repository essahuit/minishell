/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:19:41 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:19:43 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

void	ft_free(char **ar, size_t k)
{
	size_t	i;

	i = 0;
	while (i <= k)
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

void	ft_size(char **ar, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c)
			j = i;
		while (s[i] != c && s[i])
			i++;
		if (i != j)
		{
			ar[k] = ft_substr(s, j, i - j);
			if (!ar[k])
				ft_free(ar, k);
			k++;
		}
	}
}

char	**ft_split1(char const *s, char c)
{
	char	**ar;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_len(s, c);
	ar = (char **)malloc(sizeof(char *) * (j + 1));
	if (!ar)
		return (NULL);
	ft_size(ar, s, c);
	ar[j] = NULL;
	return (ar);
}

int	ft_len_ar(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

char	**ft_ar(char **arr, char *cmd)
{
	char	**ar;
	int		size;
	int		i;

	if (!arr)
		return (ft_split1(cmd, ' '));
	size = ft_len_ar(arr) + 2;
	ar = malloc(sizeof(char *) * size);
	i = 0;
	while (i < size - 1)
	{
		if (i == 0)
			ar[i] = ft_strdup(cmd);
		else
			ar[i] = ft_strdup(arr[i - 1]);
		i++;
	}
	ar[i] = NULL;
	return (ar);
}
