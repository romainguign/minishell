/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:41:45 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/08 17:48:33 by roguigna         ###   ########.fr       */
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

int	init_tmp_file(t_cmd *cmd, t_token *token)
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
	if (cmd->fd_in > 0)
		close (cmd->fd_in);
	cmd->fd_in = open(cmd->tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (cmd->fd_in == -1)
		ft_puterrors(token->next->value);
	return (1);
}
