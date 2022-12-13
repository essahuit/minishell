/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:35:13 by oaissoun          #+#    #+#             */
/*   Updated: 2022/10/18 13:35:15 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/here_doc.h"
#include "../includes/expander.h"
#include "../includes/parser.h"

int	is_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) || str[i] == '$')
			i++;
		else
			return (1);
	}
	return (0);
}

int	len_calc(char *str1, char *str2)
{
	int	ret;

	if (ft_strlen(str1) > ft_strlen(str2))
			ret = ft_strlen(str1);
	else
		ret = ft_strlen(str2);
	return (ret);
}

void	ft_write(int *fd, char *input)
{
	if (ft_strlen(input) > 0)
	{
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
	}
}

void	exec_child_heredoc(int *fd, char *lim, char **env)
{
	char	*input;
	char	*tmp;
	int		len;

	close(fd[0]);
	if (lim != NULL)
	{
		signal(SIGINT, SIG_DFL);
		input = readline(">");
		if (input)
			len = len_calc(lim, input);
		while (input && ft_strncmp(input, lim, len))
		{
			tmp = input;
			input = expand_(input, env);
			free(tmp);
			ft_write(fd, input);
			free(input);
			input = readline(">");
			if (input)
				len = len_calc(lim, input);
		}
		close(fd[1]);
	}
	exit(0);
}

int	here_doc(char *lim, char **env)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		ft_throw_error("pipe");
	pid = fork();
	if (pid == 0)
		exec_child_heredoc(fd, lim, env);
	wait(&status);
	WIFSIGNALED(status);
	if (status != 0)
	{
		WTERMSIG(status);
		if (status == SIGINT)
		{
			set(&g_vars.exit, 1);
			return (-2);
		}
	}
	close(fd[1]);
	return (fd[0]);
}
