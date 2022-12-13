/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:48:56 by oaissoun          #+#    #+#             */
/*   Updated: 2022/07/30 10:48:57 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/here_doc.h"

int	get_env_var_name(char *str, char **envp)
{
	int		i;
	char	**split_res;
	char	*res1;
	size_t	len;

	i = 1;
	while (envp[i] != NULL)
	{
		split_res = ft_split(envp[i], '=');
		res1 = split_res[0];
		len = len_calc(str, res1);
		if (ft_strncmp(res1, str, len) == 0)
		{
			free_d_arr(split_res);
			return (i);
		}
		i++;
		free_d_arr(split_res);
	}
	return (-1);
}

int	has_equal_sign(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	get_env_var_value(char **expand, int pos, char **envp)
{
	char	*tmp1;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(envp[pos]);
	*expand = ft_calloc(1, 1);
	if (has_equal_sign(envp[pos]) == 1)
		return ;
	while (i++ < len)
	{
		if (envp[pos][i] == '=')
			break ;
	}
	i++;
	if (envp[pos][i] == '\0')
		return ;
	while (envp[pos][i] != '\0')
	{
		tmp1 = *expand;
		*expand = join_char(envp[pos][i], *expand);
		free(tmp1);
		i++;
	}
}

char	*expand_str(char *str, char **envp)
{
	char	*expand;
	int		i;

	i = get_env_var_name(str, envp);
	if (i == -1)
		return (NULL);
	else
		get_env_var_value(&expand, i, envp);
	return (expand);
}

int	remove_quote_norm(int i, char quote, char *str, char **ret)
{
	char	*tmp;

	while (str[i] != quote)
	{
		tmp = *ret;
		*ret = join_char(str[i], *ret);
		free(tmp);
		i++;
	}
	return (i);
}
