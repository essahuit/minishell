/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:37:32 by oaissoun          #+#    #+#             */
/*   Updated: 2022/09/24 11:37:34 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

int	expand_squote(char *str, char **ret, int i)
{
	char	quote;
	char	*tmp;

	quote = str[i];
	i++;
	while (str[i] != quote && str[i] != '\0')
	{
		tmp = *ret;
		*ret = join_char(str[i], *ret);
		free(tmp);
		i++;
	}
	return (i);
}

int	expand_dollar_status(int i, char ***ret)
{
	char	*tmp;
	char	*tmp1;

	tmp = **ret;
	tmp1 = ft_itoa(g_vars.exit);
	**ret = ft_strjoin(**ret, tmp1);
	free(tmp);
	free(tmp1);
	i++;
	return (i);
}

void	expand_dollar_join(char *tmp, char ***ret)
{
	char	*tmp1;

	if (tmp != NULL)
	{
		tmp1 = **ret;
		**ret = ft_strjoin(**ret, tmp);
		free(tmp1);
	}
}

void	join_dollar_sign(char ***ret)
{
	char	*tmp;

	tmp = **ret;
	**ret = ft_strjoin(**ret, "$");
	free(tmp);
}

int	expand_dollar(char *str, char **ret, int i, char **envp)
{
	char	*to_expand;
	char	*tmp1;
	char	*tmp;

	to_expand = ft_calloc(1, 1);
	i++;
	if (str[i] == '?')
		i = expand_dollar_status(i, &ret);
	else if (str[i] == '\0')
		join_dollar_sign(&ret);
	else
	{
		while ((ft_isalnum(str[i]) && str[i] != '\0') || str[i] == '_')
		{
			tmp1 = to_expand;
			to_expand = join_char(str[i], to_expand);
			free(tmp1);
			i++;
		}
		tmp = expand_str(to_expand, envp);
		expand_dollar_join(tmp, &ret);
		free(tmp);
	}
	free(to_expand);
	return (i);
}
