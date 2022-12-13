/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:17:43 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/12 15:16:21 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)malloc((ft_strlen((char *)s2) + ft_strlen((char *)s1) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i + j] != '\0')
	{
		ptr[j] = s1[i + j];
		j++;
	}
	while (s2[i] != '\0')
	{
		ptr[j + i] = s2[i];
		i++;
	}
	ptr[j + i] = '\0';
	return (ptr);
}
