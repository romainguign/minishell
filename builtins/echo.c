/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:52 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/11 11:24:58 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i] && cmd[i][0])
	{
		j = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static int	echo_no_newline(char **cmd)
{
	int	i;

	i = check_n(cmd);
	if (!cmd[i])
	{
		printf("%s", "");
		return (0);
	}
	else
	{
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

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!ft_strncmp(cmd[1], "-n", 2))
		echo_no_newline(cmd);
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
