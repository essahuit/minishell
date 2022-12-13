/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:51:39 by oaissoun          #+#    #+#             */
/*   Updated: 2022/10/20 14:51:42 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/here_doc.h"

char	*remove_quote(char *str)
{
	char	*ret;
	char	*tmp;
	char	quote;
	int		i;

	i = 0;
	ret = ft_calloc(1, 1);
	while (str[i] != '\0')
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			i = remove_quote_norm(i, quote, str, &ret);
		}
		else
		{
			tmp = ret;
			ret = join_char(str[i], ret);
			free(tmp);
		}
		i++;
	}
	return (ret);
}

int	ft_check(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == '_' || c == '?')
		return (1);
	else
		return (0);
}

int	roll_back(int i, char *str)
{
	if (str[i] == '$')
		i--;
	return (i);
}

int	expand_dquote(char *str, char **ret, int i, char **envp)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] != quote && str[i] != '\0')
	{
		if (my_ft_isprint(str[i], '$'))
			expand_dquote_join(&ret, str, i);
		else
		{
			if (str[i + 1] == '\'' || !ft_check(str[i + 1]))
				expand_dquote_join(&ret, str, i);
			else
			{
				i++;
				if (str[i] == '?')
					i = expand_dquote_status(&ret, i);
				i = expand_dquote_(&ret, str, i, envp);
			}
		}
		if (str[i] != quote)
			i++;
	}
	return (i);
}
