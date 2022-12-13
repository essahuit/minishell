/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:49:01 by oaissoun          #+#    #+#             */
/*   Updated: 2022/07/30 10:49:04 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	expand_dquote_join(char ***ret, char *str, int i)
{
	char	*tmp1;

	tmp1 = **ret;
	**ret = join_char(str[i], **ret);
	free(tmp1);
}

int	expand_dquote_status(char ***ret, int i)
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

void	expand_dquote_join_sq(char ***ret, char *str, int i)
{
	char	*tmp1;

	if (str[i] == '\'')
	{
		tmp1 = **ret;
		**ret = join_char(str[i], **ret);
		free(tmp1);
	}
}

void	expand_dquote_join_char(char ***ret, char *str, int i)
{
	char	*tmp1;

	if (str[i] != '"' && str[i] != '\'')
	{
		tmp1 = **ret;
		**ret = join_char(str[i], **ret);
		free(tmp1);
	}
}

int	expand_dquote_(char ***ret, char *str, int i, char **envp)
{
	char	*tmp;
	char	*tmp1;
	char	*to_expand;

	to_expand = ft_calloc(1, 1);
	while (ft_check(str[i]) && str[i] != '"')
	{
		tmp1 = to_expand;
		to_expand = join_char(str[i], to_expand);
		free(tmp1);
		i++;
	}
	tmp = expand_str(to_expand, envp);
	if (tmp != NULL)
	{
		tmp1 = **ret;
		**ret = ft_strjoin(**ret, tmp);
		free(tmp1);
	}
	expand_dquote_join_char(ret, str, i);
	free(tmp);
	free(to_expand);
	expand_dquote_join_sq(ret, str, i);
	i = roll_back(i, str);
	return (i);
}
