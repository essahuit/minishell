/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:43:00 by oaissoun          #+#    #+#             */
/*   Updated: 2022/07/30 10:43:01 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	func(t_command **cmd, t_command **temp)
{
	size_t		i;
	size_t		len;
	t_command	*temp1;

	i = 1;
	temp1 = (*temp)->next;
	len = ft_strlen2((*temp)->arr);
	(*temp)->next = create_list((*temp)->arr[0], STRING);
	while (i < len)
	{
		if ((*temp)->next->arr == NULL)
				(*temp)->next->arr = init_arr((*cmd)->arr[i]);
		else
			(*temp)->next->arr = add_to_arr((*temp)->next->arr, (*cmd)->arr[i]);
		i++;
	}
	free_d_arr((*cmd)->arr);
	(*cmd)->arr = NULL;
	(*temp)->next->next = temp1;
}

void	init_(size_t *i, size_t *len, char **arr)
{
	*i = 0;
	*len = ft_strlen2(arr);
}

void	func1(t_command **cmd, t_command **temp)
{
	size_t	i;
	size_t	len;

	while ((*cmd) && (*cmd)->token != PIPE)
	{
		if ((*cmd)->arr != NULL)
		{
			init_(&i, &len, (*cmd)->arr);
			while (i < len)
			{
				if ((*temp)->arr == NULL)
					(*temp)->arr = init_arr((*cmd)->arr[i]);
				else
				{
					g_vars.tmp = (*temp)->arr;
					(*temp)->arr = add_to_arr((*temp)->arr, (*cmd)->arr[i]);
					free(g_vars.tmp);
				}
				i++;
			}
		}
		free_d_arr((*cmd)->arr);
		(*cmd)->arr = NULL;
		(*cmd) = (*cmd)->next;
	}
}

void	last_touches(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		if (cmd->token == PIPE)
			cmd = cmd->next;
		else if (cmd->token == STRING)
		{
			temp = cmd;
			cmd = cmd->next;
			func1(&cmd, &temp);
		}
		else if (cmd->token == RREDIR || cmd->token == LREDIR
			|| cmd->token == APPENDREDIR || cmd->token == HEREDOC)
		{
			temp = cmd;
			if (temp->arr != NULL)
				func(&cmd, &temp);
			cmd = cmd->next;
		}
	}
}

int	is_operator(t_lexer *lexer)
{
	if (lexer->token->e_type == RREDIR || lexer->token->e_type == LREDIR
		|| lexer->token->e_type == APPENDREDIR
		|| lexer->token->e_type == HEREDOC)
		return (1);
	return (0);
}
