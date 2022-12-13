/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:07:36 by oaissoun          #+#    #+#             */
/*   Updated: 2022/06/16 12:07:38 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/expander.h"
#include "../includes/here_doc.h"

void	get_operator(t_lexer *lexer, t_command **command)
{
	char		*data;
	int			token;

	data = NULL;
	token = lexer->token->e_type;
	if (lexer->token->e_type == RREDIR)
		eat(lexer, RREDIR);
	else if (lexer->token->e_type == LREDIR)
		eat(lexer, LREDIR);
	else if (lexer->token->e_type == APPENDREDIR)
		eat(lexer, APPENDREDIR);
	else if (lexer->token->e_type == HEREDOC)
		eat(lexer, HEREDOC);
	if (lexer->token->e_type == STRING)
		data = lexer->token->value;
	eat(lexer, STRING);
	*command = create_list(data, token);
	if (data)
		free(data);
}

t_command	*operator(t_lexer *lexer)
{
	t_command	*command;
	char		*str;
	char		**tmp;

	command = NULL;
	if (is_operator(lexer))
		get_operator(lexer, &command);
	while (lexer->token->e_type == STRING)
	{
		if (command->arr == NULL)
			command->arr = init_arr(lexer->token->value);
		else
		{
			tmp = command->arr;
			command->arr = add_to_arr(command->arr, lexer->token->value);
			free(tmp);
		}
		str = lexer->token->value;
		eat(lexer, STRING);
		free(str);
	}
	if (lexer->syn == 1)
		command->err = 1;
	return (command);
}

void	is_cmd_string(t_lexer *lexer, t_command **command, t_command **op)
{
	char	*str;

	*command = create_list(lexer->token->value, lexer->token->e_type);
	str = lexer->token->value;
	eat(lexer, STRING);
	free(str);
	while (lexer->token->e_type == STRING)
	{
		if ((*command)->arr == NULL)
			(*command)->arr = init_arr(lexer->token->value);
		else
		{
			g_vars.tmp = (*command)->arr;
			(*command)->arr = add_to_arr((*command)->arr, lexer->token->value);
			free(g_vars.tmp);
		}
		str = lexer->token->value;
		eat(lexer, STRING);
		free(str);
	}
	while (is_operator(lexer))
	{
		*op = operator(lexer);
		concat_lists(*command, *op);
	}
}

t_command	*command_(t_lexer *lexer)
{
	t_command	*command;
	t_command	*op;
	t_command	*tmp;

	command = NULL;
	op = NULL;
	if (lexer->token->e_type == STRING)
		is_cmd_string(lexer, &command, &op);
	else if (is_operator(lexer))
	{
		op = operator(lexer);
		while (is_operator(lexer))
		{
			tmp = operator(lexer);
			concat_lists(op, tmp);
		}
	}
	else
		eat(lexer, STRING);
	if (!command)
		return (op);
	return (command);
}

t_command	*list(t_lexer *lexer)
{
	t_command	*command;
	t_command	*tmp;

	tmp = NULL;
	command = NULL;
	if (lexer->token->e_type == END)
		return (NULL);
	if (ft_strlen(lexer->content))
	{
		command = command_(lexer);
		if (command != NULL)
		{
			while (lexer->token->e_type == PIPE)
			{
				add_to_list(command, lexer->token->value, lexer->token->e_type);
				eat(lexer, PIPE);
				tmp = command_(lexer);
				concat_lists(command, tmp);
			}
		}
	}
	return (command);
}
