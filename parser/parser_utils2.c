/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:15:01 by oaissoun          #+#    #+#             */
/*   Updated: 2022/09/25 11:15:02 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	eat(t_lexer *lexer, int i)
{
	t_token	*tmp1;

	tmp1 = NULL;
	if ((int)lexer->token->e_type == i)
	{
		tmp1 = lexer->token;
		lexer->token = get_next_token(lexer);
		if (tmp1 != NULL)
			free(tmp1);
	}
	else
	{
		lexer->syn = 1;
		set(&g_vars.exit, 258);
	}
}

void	siginthandle(int signal)
{
	if (signal == SIGINT)
	{
		if (errno == EINTR)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			set(&g_vars.exit, 1);
		}
	}
}

size_t	ft_strlen2(char	**s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

void	print_list(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		if (cmd->token == LREDIR || cmd->token == RREDIR
			|| cmd->token == HEREDOC || cmd->token == APPENDREDIR)
			printf("%d ", cmd->token);
		printf("-> %s ", cmd->data);
		if (cmd->arr != NULL)
		{
			i = 0;
			while (cmd->arr[i] != NULL)
			{
				printf("%s ", cmd->arr[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
	printf("\n");
}

void	free_d_arr(char **arr)
{
	size_t		i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}
