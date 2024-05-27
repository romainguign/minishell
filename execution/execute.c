/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/27 13:52:17 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execution(char **cmd, char **envp, t_minishell *infos)
{
	exec_builtin(cmd, infos);
	if (cmd[0])
	{
		signal_handler(1);
		execve(cmd[0], cmd, envp);
		// ft_putstr_fd("execve : ", 2);
		ft_puterrors(cmd[0]);
	}
	ft_free_env(envp);
	free_all(infos);
	close_std();
	exit(EXIT_FAILURE);
}

void	create_pids(int (*pipes)[2], char **envp, t_minishell *infos, int i)
{
	t_cmd	*tmp;
	pid_t	pids[512];

	tmp = infos->cmd;
	while (tmp)
	{
		pids[i] = fork();
		g_signal_receive = 1;
		if (pids[i] == -1)
		{
			close_pipes(pipes, infos->cmd);
			free_all(infos);
			perror("minishell: fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			if (!children_process(pipes, i, tmp, infos))
			{
				ft_free_env(envp);
				exit(EXIT_FAILURE);
			}
			check_access(tmp->redir);
			check_cmds(tmp, infos->env, infos);
			ft_execution(tmp->cmd, envp, infos);
			close_fds(infos->cmd);
		}
		i++;
		tmp = tmp->next;
	}
	wait_and_close(infos, pids, pipes);
}

void	start_program(char **envp, t_minishell *infos)
{
	int		pipes[512][2];
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = infos->cmd;
	while (tmp && i < 512)
	{
		if (pipe(pipes[i]) == -1)
		{
			close_pipes(pipes, infos->cmd);
			perror("minishell");
			return ;
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
	if (!only_builtin(infos))
	{
		ft_free_env(envp);
		return (0);
	}
	start_program(envp, infos);
	ft_free_env(envp);
	return (1);
}
