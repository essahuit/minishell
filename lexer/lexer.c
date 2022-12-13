/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:47:48 by oaissoun          #+#    #+#             */
/*   Updated: 2022/06/16 11:47:49 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char	*join_char(char c, char *str)
{
	char	*cpy;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	cpy = malloc(len + 2);
	i = 0;
	while (i < len)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = c;
	cpy[i + 1] = '\0';
	return (cpy);
}

void	ft_throw_error(char	*err)
{
	int	len;

	len = ft_strlen(err);
	write(2, err, len);
	write(2, "\n", 1);
}

int	my_ft_isprint(int c, char except)
{
	if (c > 31 && c < 127)
	{
		if (c == except)
			return (0);
		return (1);
	}
	else
		return (0);
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_whitespace(lexer);
		if (lexer->c == '\'')
			return (get_string(lexer));
		if (lexer->c == '"')
			return (get_string(lexer));
		if (lexer->c == '<')
		{
			if (lexer->content[lexer->i + 1] == '<')
			{
				lexer_advance(lexer);
				return (get_(lexer, HEREDOC, "<<"));
			}
			return (get_(lexer, LREDIR, "<"));
		}
		return (get_next_token2(lexer));
	}
	return (create_token(END, NULL));
}

void	set(int *var, int val)
{
	*var = val;
}
