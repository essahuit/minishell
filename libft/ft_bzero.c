/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:36:05 by oaissoun          #+#    #+#             */
/*   Updated: 2021/11/05 13:05:25 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	ft_bzero(void	*s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}
