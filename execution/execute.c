/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/27 14:43:56 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execution(char **cmd, char **envp, t_minishell *infos)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		ft_puterrors(cmd[0]);
		free_all(infos);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	children_process(int (*pipes)[2], int i, t_cmd *cmd, t_minishell *infos)
{
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		close_pipes(pipes, infos->cmd);
		return ;
	}
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
	if (cmd->fd_in > 0)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			perror("minishell: dup2");
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
	close_pipes(pipes, infos->cmd);
}

void	create_pids(int (*pipes)[2], char **envp, t_minishell *infos, int i)
{
	t_cmd	*tmp;
	pid_t	pids[512];

	tmp = infos->cmd;
	while (tmp)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			close_pipes(pipes, infos->cmd);
			free_all(infos);
			perror("minishell: fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			children_process(pipes, i, tmp, infos);
			ft_execution(tmp->cmd, envp, infos);
			free_all(infos);
			exit(EXIT_FAILURE);
		}
		i++;
		tmp = tmp->next;
	}
	wait_and_close(infos, pids, pipes);
}

void	start_program(char **envp, t_minishell *infos)
{
	int	pipes[512][2];
	int	i;
	t_cmd *tmp;

	i = 0;
	tmp = infos->cmd;
	while (tmp)
	{
		if (pipe(pipes[i]) == -1)
		{
			close_pipes(pipes, infos->cmd);
			free_all(infos);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	create_pids(pipes, envp, infos, i);
}

int	ft_execute(t_minishell *infos)
{
	char	**envp;
	
	if (!make_lstcmd(infos))
		return (0);
	envp = lst_to_tab(infos->env);
	if (!envp)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	check_cmds(infos->cmd, infos->env);
	start_program(envp, infos);
	ft_free_env(envp);
	return (1);
}
