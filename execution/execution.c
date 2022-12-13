/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:20:48 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:20:50 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

void	close_dup(t_data data, int in, int out)
{
	closing(&data);
	close(data.infile);
	close(data.outfile);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

void	ft_status(void)
{
	int	status;

	if (g_vars.err != 2 && g_vars.exit == -1)
	{
		waitpid(g_vars.pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (status == SIGINT)
				set(&g_vars.exit, 130);
			if (status == SIGQUIT)
				set(&g_vars.exit, 131);
		}
		if (WIFEXITED(status))
			set(&g_vars.exit, WEXITSTATUS(status));
	}
}

void	pipe_alloc(t_data data)
{
	int	i;

	i = 0;
	while (i < data.size)
	{
		data.fd[i] = malloc(sizeof(int) * 2);
		if (pipe(data.fd[i]) < 0)
			ft_throw_error("pipe error");
		i++;
	}
}

void	init_v(t_data *data)
{
	data->pos = 0;
	data->infile = -1;
	data->outfile = -1;
}

void	execute(t_command *command, char **envp, t_env **env_t)
{
	t_data	data;
	int		i;
	int		in;
	int		out;

	in = dup(0);
	out = dup(1);
	g_vars.reserv = dup(1);
	i = 0;
	init_v(&data);
	data.size = ft_lstcommandsize(command);
	data.fd = malloc(sizeof(int *) * data.size);
	data.env = envp;
	if (!data.fd)
		return ;
	pipe_alloc(data);
	exec(command, &data, env_t, envp);
	close_dup(data, in, out);
	ft_status();
	while (1)
	{
		if (waitpid(0, NULL, 0) == -1)
			break ;
	}
}
