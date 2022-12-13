/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:40:16 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/14 20:25:52 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	find_pos_front(char const *s1, char const *set)
{
	int	set_count;
	int	s_count;
	int	set_len;

	set_len = ft_strlen((char *)set);
	s_count = 0;
	while (s1[s_count] != '\0')
	{
		set_count = 0;
		while (set[set_count] != '\0')
		{
			if (s1[s_count] == set[set_count])
				break ;
			set_count++;
		}
		if (set_count == set_len)
			break ;
		s_count++;
	}
	return (s_count);
}

static int	find_pos_back(char const *s1, char const *set)
{
	int	set_count;
	int	s_count;
	int	set_len;

	set_len = ft_strlen((char *)set);
	s_count = ft_strlen((char *)s1) - 1;
	while (s_count > 0)
	{
		set_count = 0;
		while (set[set_count] != '\0')
		{
			if (s1[s_count] == set[set_count])
				break ;
			set_count++;
		}
		if (set_count == set_len)
			break ;
		s_count--;
	}
	return (s_count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		front_pos;
	int		pos;
	char	*ptr;
	int		len;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	front_pos = find_pos_front(s1, set);
	len = find_pos_back(s1, set) - front_pos + 1;
	if (len < 0)
		len = 0 ;
	pos = 0;
	ptr = malloc((sizeof(char) * (len + 1)));
	if (ptr == NULL)
		return (NULL);
	while (pos < len)
	{
		ptr[pos] = s1[front_pos + pos];
		pos++;
	}
	ptr[pos] = '\0';
	return (ptr);
}
