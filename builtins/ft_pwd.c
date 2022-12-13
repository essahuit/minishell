/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:42:02 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/19 05:42:06 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/execution.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd)
		printf("%s\n", pwd);
	else
		printf("%s\n", g_vars.pwd);
	free(pwd);
	return (0);
}
