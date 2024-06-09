/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:52 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/09 15:18:12 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!ft_strncmp(cmd[1], "-n", 2))
	{
		if (!cmd[2])
		{
			printf("%s", "");
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
				printf("%s ", cmd[i]);
			else
				printf("%s\n", cmd[i]);
			i++;
		}
		return (0);
	}
	return (1);
}
