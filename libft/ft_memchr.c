/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:17:19 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/05 14:24:30 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	x;

	ptr = (unsigned char *)s;
	i = 0;
	x = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == x)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
