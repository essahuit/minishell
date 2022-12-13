/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:47:19 by oaissoun          #+#    #+#             */
/*   Updated: 2022/10/21 16:47:20 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/expander.h"
#include "./includes/lexer.h"
#include "./includes/here_doc.h"
#include "./includes/execution.h"

void	free_cmd(t_command **cmd)
{
	t_command	*tmp;

	while (*cmd)
	{
		if ((*cmd)->data)
			free((*cmd)->data);
		if ((*cmd)->arr)
			free_d_arr((*cmd)->arr);
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free(tmp);
	}
}

void	free_all(char *input, t_command **command, t_lexer **lexer)
{
	free(input);
	free_cmd(command);
	free((*lexer)->content);
	free((*lexer)->token);
	free((*lexer));
}

void	free_all_syn(char *input, t_lexer **lexer)
{
	free(input);
	free((*lexer)->content);
	free((*lexer)->token->value);
	free((*lexer)->token);
	free((*lexer));
}

char	*ft_main(int argc, char *argv[])
{
	char	*input;

	if (argc > 1 && argv)
	{
		printf("invalid argument\n");
		exit(127);
	}
	input = readline("minishell>>-0.0$ ");
	return (input);
}
