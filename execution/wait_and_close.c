/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:52:39 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/27 13:56:11 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_std(void)
{
	close(0);
	close(1);
	close(2);
}

static void	check_status(int status, t_minishell *infos)
{
	if (WIFEXITED(status))
		infos->exit_code = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
		infos->exit_code = WSTOPSIG(status);
	if (WIFCONTINUED(status))
		infos->exit_code = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	wait_end(t_minishell *infos, pid_t *pids)
{
	int		i;
	int		status;
	t_cmd	*tmp;

	i = 0;
	tmp = infos->cmd;
	while (tmp)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("minishell: waitpid");
			exit(EXIT_FAILURE);
		}
		check_status(status, infos);
		tmp = tmp->next;
		i++;
	}
	g_signal_receive = 0;
}

void	close_pipes(int (*pipes)[2], t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp && i < 510)
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
	while (tmp && i < 510)
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

void	free_close(t_minishell *infos)
{
	// free_all(infos);	
}