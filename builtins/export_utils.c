/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:10:25 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/03 07:26:53 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_wrong_identifier2(char c)
{
	if ((c >= '#' && c <= '*') || (c >= ',' && c <= '/')
		|| (c >= ':' && c <= '<') || (c >= '>' && c <= '@')
		|| (c >= '[' && c <= '^') || (c >= '{' && c <= '~'))
		return (1);
	return (0);
}

int	define_type_argument(char *cmd)
{
	int i;
	
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '+')
			return (2);
		else if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

// void check_type(char *cmd)
// {
// 	if (define_type_argument(cmd) == 0)
// 	{
		
// 	}
// 	else if (define_type_argument(cmd) == 1)
// 	{
// 	}
// 	else if (define_type_argument(cmd) == 2)
// 	{
		
// 	}
// }

int	is_input_correct(char *str)
{
	int i;
	
	i = 1;
	if (is_wrong_identifier(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] != '=')
				return (0);
		}
		if (is_wrong_identifier2(str[i]))
		{
			return (0);
		}
		i++;
	}
	return(1);
}