/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:41:45 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/24 15:48:46 by roguigna         ###   ########.fr       */
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
	cmd->tmp_file = ft_strdup(".00000000000000000000");
	if (!cmd->tmp_file)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	create_tmp_filename(cmd->tmp_file);
	cmd->fd_in = open(cmd->tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (cmd->fd_in == -1)
		ft_puterrors(token->next->value);
	return (1);
}

void	ft_create_tmp_file(int infile, char *doc, char *limiter,
	int len_limiter)
{
	// int	i;
	// int	j;

	// i = 0;
	// j = 0;
	// if (ft_cmp_lastline(limiter, doc, len_limiter) == 0)
	// {
	// 	while (doc[i])
	// 		i++;
	// 	i -= 2;
	// 	while (i >= 0 && doc[i] != '\n')
	// 		i--;
	// 	write(infile, doc, i + 1);
	// }
	// else
		ft_putstr_fd(doc, infile);
}