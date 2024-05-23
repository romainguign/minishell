/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:59:57 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/23 12:45:40 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_error(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int ft_exit(char **cmd)
{
	int size_cmd;

	size_cmd = ft_tab_len(cmd);
	if (size_cmd > 2)
	{
		print_exit_error("");
	}
	else
	{
		if (size_cmd == 2)
		{
			//check if it's number
		}
		if (size_cmd == 1)
		{
			//exit() avec le dernier exit code process
		}
	}
	return (0);
}