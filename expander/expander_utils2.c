/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:35:07 by oaissoun          #+#    #+#             */
/*   Updated: 2022/10/18 16:35:08 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

int	expand_join(char **ret, char *str, int i)
{
	char	*tmp;

	tmp = *ret;
	*ret = join_char(str[i], *ret);
	free(tmp);
	i++;
	return (i);
}

int	expand_flag(char *str, int *flag, int i)
{
	if ((str[i] == '"' || str[i] == '\'') && *flag == 1)
	{
		i++;
		flag = 0;
	}
	return (i);
}

void	expand_init(int *i, int *flag, char **ret)
{
	*i = 0;
	*flag = 0;
	*ret = ft_calloc(1, 1);
}

char	*expand_(char *str, char	**envp)
{
	char	*ret;
	int		flag;
	int		i;

	expand_init(&i, &flag, &ret);
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i = expand_dquote(str, &ret, i, envp);
			flag = 1;
		}
		else if (str[i] == '\'')
		{
			i = expand_squote(str, &ret, i);
			flag = 1;
		}
		else if (str[i] == '$')
			i = expand_dollar(str, &ret, i, envp);
		else
			i = expand_join(&ret, str, i);
		i = expand_flag(str, &flag, i);
	}
	return (ret);
}

void	expand_command(t_command *cmd, char	**envp)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		tmp = cmd->data;
		if (cmd->token != HEREDOC)
			cmd->data = expand_(cmd->data, envp);
		else
			cmd->data = remove_quote(cmd->data);
		free(tmp);
		if (cmd->arr != NULL)
		{
			i = 0;
			while (cmd->arr[i] != NULL)
			{
				tmp = cmd->arr[i];
				cmd->arr[i] = expand_(cmd->arr[i], envp);
				free(tmp);
				i++;
			}
		}
		cmd = cmd->next;
	}
}
