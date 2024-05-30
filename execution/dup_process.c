/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:40:15 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/30 18:56:45 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_pipes(int (*pipes)[2], int i, t_cmd *cmd, t_minishell *infos)
{
	if (i > 0 && cmd->fd_in == 0)
	{
		if (dup2(pipes[i - 1][0], 0) == -1)
			perror("minishell: dup2");
	}
	if (cmd->next != NULL && cmd->fd_out == 1)
	{
		if (dup2(pipes[i][1], 1) == -1)
			perror("minishell: dup2");
		close_pipes(pipes, infos->cmd);
	}
}

static void	dup_fds(int (*pipes)[2], t_cmd *cmd, t_minishell *infos)
{
	if (cmd->fd_in > 0)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			perror("minishell: dup2");
		if (cmd->tmp_file)
			unlink(cmd->tmp_file);
		close(cmd->fd_in);
		close_pipes(pipes, infos->cmd);
	}
	if (cmd->fd_out > 1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			perror("minishell: dup2");
		close(cmd->fd_out);
		close_pipes(pipes, infos->cmd);
	}
}

int	children_process(int (*pipes)[2], int i, t_cmd *cmd, t_minishell *infos)
{
	ft_redirects(cmd,  infos);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		close_pipes(pipes, infos->cmd);
		free_all(infos);
		close_std();
		exit(1);
	}
	dup_pipes(pipes, i, cmd, infos);
	dup_fds(pipes, cmd, infos);
	close_pipes(pipes, infos->cmd);
	return (1);
}
