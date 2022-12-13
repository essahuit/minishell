/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:41:02 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/16 16:42:39 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			x;

	i = 0;
	x = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == x)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == x)
		return ((char *)(s + i));
	return (NULL);
}
