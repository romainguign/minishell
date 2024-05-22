/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:59:57 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/21 12:34:38 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_lstsize_token(t_token *token)
{
	t_token *tmp;
	int		i;
	
	tmp = token;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	print_exit_error(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void ft_exit(t_token *token)
{
	int size_cmd;

	size_cmd = ft_lstsize_token(token);
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
}