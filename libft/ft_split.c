/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:50:18 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/10 10:19:06 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static int	find_word_count(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	if (s == NULL)
		return (0);
	if (s[0] != c)
		word_count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			word_count++;
		i++;
	}
	return (word_count);
}

static char	*extract_word(char const *s, int from, int to)
{
	char	*ptr;
	int		s_len;
	int		i;

	s_len = to - from + 1;
	i = 0;
	ptr = malloc (sizeof (char) * (s_len + 1));
	while (s_len > i)
	{
		ptr[i] = s[from + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**fill(char **ptr, char const *s, char c)
{
	int		i;
	int		from;
	int		ptr_count;
	int		to;

	i = 0;
	ptr_count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			from = i;
			to = i;
			while (s[to] != c && s[to] != '\0')
				to++;
			ptr[ptr_count] = extract_word(s, from, to - 1);
			ptr_count++;
			i = to - 1;
		}
		i++;
	}
	ptr[ptr_count] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (s == NULL)
		return (NULL);
	ptr = malloc(sizeof(char *) * (find_word_count(s, c) + 1));
	if (ptr == NULL)
		return (NULL);
	return (fill(ptr, s, c));
}
