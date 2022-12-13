/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:34:52 by oaissoun          #+#    #+#             */
/*   Updated: 2022/06/24 12:34:54 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_command	*create_list(char *data, int i)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->data = ft_strdup(data);
	command->arr = NULL;
	command->next = NULL;
	command->token = i;
	command->heredoc = -1;
	command->err = 0;
	return (command);
}

void	add_to_list(t_command *lst, char *data, int i)
{
	while (lst->next)
		lst = lst->next;
	lst->next = create_list(data, i);
}

void	concat_lists(t_command *lst, t_command *lst1)
{
	while (lst->next)
		lst = lst->next;
	lst->next = lst1;
}

char	**add_to_arr(char **arr, char *str)
{
	int		i;
	int		len;
	char	**ret;

	i = 0;
	len = ft_strlen2(arr);
	ret = malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		ret[i] = arr[i];
		i++;
	}
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	return (ret);
}

char	**init_arr(char	*str)
{
	char	**ret;

	ret = malloc(sizeof(char *) * 2);
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}
