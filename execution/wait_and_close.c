/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:52:39 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/26 18:18:29 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_std(void)
{
	close(0);
	close(1);
	close(2);
}

void	wait_end(t_minishell *infos, pid_t *pids)
{
	int	i;
	t_cmd *tmp;

	i = 0;
	tmp = infos->cmd;
	while (tmp)
	{
		if (waitpid(pids[i], NULL, 0) == -1)
		{
			perror("minishell: waitpid");
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
		i++;
	}
}

void	close_pipes(int (*pipes)[2], t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp && i < 509)
	{
		if (pipes[i][0])
			close(pipes[i][0]);
		if (pipes[i][1])
			close(pipes[i][1]);
		i++;
		tmp = tmp->next;
	}
}

void	close_fds(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp && i < 509)
	{
		if (tmp->fd_in > 0)
			close(tmp->fd_in);
		if (tmp->fd_out > 1)
			close(tmp->fd_out);
		i++;
		tmp = tmp->next;
	}
}

void	wait_and_close(t_minishell *infos, pid_t *pids, int (*pipes)[2])
{
	close_pipes(pipes, infos->cmd);
	close_fds(infos->cmd);
	wait_end(infos, pids);
}