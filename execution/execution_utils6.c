/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:20:14 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:20:16 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

void	get_files_rredir(t_command *temp, t_data *data)
{
	if (data->outfile != -1)
		close(data->outfile);
	data->outfile = open(temp->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		if (ft_strlen(temp->data) == 0)
			ft_throw_error("ambigious redir");
		else
			ft_throw_error("file not found");
		g_vars.err = 2;
		set(&g_vars.exit, 1);
	}
}

void	get_files_lredir(t_command *temp, t_data *data)
{
	if (data->infile != -1)
		close(data->infile);
	data->infile = open(temp->data, O_RDONLY);
	if (data->infile == -1)
	{
		if (ft_strlen(temp->data) == 0)
			ft_throw_error("ambigious redir");
		else
			ft_throw_error("file not found");
		g_vars.err = 2;
		set(&g_vars.exit, 1);
	}
}

void	get_files_append(t_command *temp, t_data *data)
{
	if (data->outfile != -1)
		close(data->outfile);
	data->outfile = open(temp->data, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->outfile == -1)
	{
		if (ft_strlen(temp->data) == 0)
			ft_throw_error("ambigious redir");
		else
			ft_throw_error("file not found");
		g_vars.err = 2;
		set(&g_vars.exit, 1);
	}
}

void	check_files(t_data *data)
{
	if (data->infile != -1)
	{
		close(data->infile);
		data->infile = -1;
	}
	if (data->outfile != -1)
	{
		close(data->outfile);
		data->outfile = -1;
	}
}

void	get_files(t_command *command, t_data *data)
{
	t_command	*temp;

	temp = command;
	check_files(data);
	while (temp && temp->token != PIPE)
	{
		if (g_vars.err == 2)
			return ;
		if (temp->token == RREDIR)
			get_files_rredir(temp, data);
		else if (temp->token == LREDIR)
			get_files_lredir(temp, data);
		else if (temp->token == APPENDREDIR)
			get_files_append(temp, data);
		else if (temp->token == HEREDOC)
			data->infile = temp->heredoc;
		temp = temp->next;
	}
}
