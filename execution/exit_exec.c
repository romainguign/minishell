/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:11:38 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 19:13:53 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(long long int builtin, t_minishell *infos)
{
	int		tmp_exit_code;

	if (builtin != -2 && !ft_strcmp(infos->cmd->cmd[0], "exit")
		&& !infos->cmd->next)
	{
		if (builtin == -1)
		{
			infos->exit_code = 1;
			return (1);
		}
		tmp_exit_code = infos->exit_code;
		free_all(infos);
		exit(tmp_exit_code);
	}
	return (0);
}
