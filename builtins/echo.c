/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:52 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/23 11:11:18 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if(!ft_strcmp(cmd[1], "-n"))
	{
		
		if (!cmd[2])
		{
			printf("");
			return (0);
		}
		else
		{
			i++;
			while (cmd[i])
			{
				if (cmd[i + 1] != NULL)
					printf("%s ", cmd[i]);
				else
					printf("%s", cmd[i]);
				i++;
			}
			return (0);
		}
	}
	else
	{
		while (cmd[i])
		{
			if (cmd[i + 1] != NULL)
			{
				printf("%s ",cmd[i]);
			}
			else
			
				printf("%s\n", cmd[i]);
			i++;
		}
		return (0);
	}
	return (1);
}