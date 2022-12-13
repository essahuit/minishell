/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:18:20 by oaissoun          #+#    #+#             */
/*   Updated: 2022/06/13 12:18:23 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/lexer.h"

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

void	f1(t_lexer *lexer, char quote, char **quoted)
{
	char	*tmp1;

	while (lexer->c != quote)
	{
		if (lexer->c == '\0')
		{
			ft_throw_error("unclosed quote");
			lexer->syn = 2;
			break ;
		}
		tmp1 = *quoted;
		*quoted = join_char(lexer->c, *quoted);
		free(tmp1);
		lexer_advance(lexer);
	}
}

void	get_quoted(t_lexer *lexer, char **value)
{
	char	quote;
	char	*quoted;
	char	*tmp;

	quote = lexer->c;
	quoted = malloc(2);
	quoted[0] = lexer->c;
	quoted[1] = '\0';
	lexer_advance(lexer);
	f1(lexer, quote, &quoted);
	tmp = *value;
	*value = ft_strjoin(*value, quoted);
	free(quoted);
	free(tmp);
	tmp = *value;
	*value = join_char(quote, *value);
	free(tmp);
}

t_token	*get_string(t_lexer *lexer)
{
	char	*value;
	char	*tmp;

	value = ft_calloc(1, 1);
	while (lexer->c != '\0' && ft_isprint(lexer->c))
	{
		if (lexer->c == ' ' && ft_strlen(value) > 0)
			break ;
		if (is_quote(lexer->c))
			get_quoted(lexer, &value);
		else
		{
			tmp = value;
			value = join_char(lexer->c, value);
			free(tmp);
		}
		lexer_advance(lexer);
	}
	return (create_token(STRING, value));
}

t_token	*get_next_token2(t_lexer *lexer)
{
	if (lexer->c == '>')
	{
		if (lexer->content[lexer->i + 1] == '>')
		{
			lexer_advance(lexer);
			return (get_(lexer, APPENDREDIR, ">>"));
		}
		return (get_(lexer, RREDIR, ">"));
	}
	if (lexer->c == '|')
		return (get_(lexer, PIPE, "|"));
	if (lexer->c == '$')
		return (get_string(lexer));
	if (ft_isprint(lexer->c))
		return (get_string(lexer));
	return (create_token(END, NULL));
}
