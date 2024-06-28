/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:41:45 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 18:04:26 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chars_index(char c)
{
	int	i;

	i = 0;
	while (BASE[i] && BASE[i] != c)
		i++;
	return (i);
}

void	create_tmp_filename(char *tmp_file)
{
	int	i;

	while (access(tmp_file, F_OK) == 0)
	{
		i = 1;
		while (tmp_file[i] == 'Z')
		{
			tmp_file[i] = '0';
			i++;
		}
		tmp_file[i] = BASE[chars_index(tmp_file[i]) + 1];
	}
}

int	init_tmp_file(t_cmd *cmd)
{
	if (cmd->tmp_file)
	{
		if (access(cmd->tmp_file, F_OK | R_OK | W_OK) == 0)
			unlink(cmd->tmp_file);
		free(cmd->tmp_file);
		cmd->tmp_file = NULL;
	}
	cmd->tmp_file = ft_strdup(".00000000000000000000");
	if (!cmd->tmp_file)
		return (0);
	create_tmp_filename(cmd->tmp_file);
	return (1);
}
