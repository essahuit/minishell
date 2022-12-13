/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:11:07 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/12 15:13:36 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ptr_dst;
	char	*ptr_src;
	size_t	i;

	ptr_dst = (char *) dst;
	ptr_src = (char *) src;
	if (len == 0)
		return (dst);
	if (ptr_src < ptr_dst)
	{
		i = len - 1;
		while (i > 0)
		{
			ptr_dst[i] = ptr_src[i];
			i--;
		}
		ptr_dst[0] = ptr_src[0];
	}
	else if (ptr_src > ptr_dst)
	{
		ft_memcpy(ptr_dst, ptr_src, len);
	}
	return (dst);
}
