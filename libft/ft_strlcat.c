/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:51:35 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/14 20:23:54 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;
	size_t	j;

	src_len = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (src_len);
	dest_len = ft_strlen((const char *)dst);
	i = dest_len;
	j = 0;
	if (dest_len >= dstsize)
		return (src_len + dstsize);
	else
	{
		while (src[j] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (dest_len + src_len);
	}
}
