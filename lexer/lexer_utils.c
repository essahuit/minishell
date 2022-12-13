/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:26:51 by oaissoun          #+#    #+#             */
/*   Updated: 2022/06/13 13:26:52 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/lexer.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->content = ft_strdup(content);
	lexer->i = 0;
	lexer->c = content[lexer->i];
	lexer->syn = 0;
	lexer->token = get_next_token(lexer);
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];
	}
}

void	skip_whitespace(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		while (lexer->c == ' ' || lexer->c == '\t')
			lexer_advance(lexer);
	}
}

t_token	*create_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->e_type = type;
	token->value = value;
	return (token);
}

t_token	*get_(t_lexer *lexer, int i, char *val)
{
	lexer_advance(lexer);
	return (create_token(i, val));
}
