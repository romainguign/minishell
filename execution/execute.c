/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/07 19:46:12 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execution(char **cmd, char **envp, t_minishell *infos)
{
	exec_builtin(cmd, infos);
	if (cmd[0])
	{
		execve(cmd[0], cmd, envp);
		ft_puterrors(cmd[0]);
	}
	ft_free_env(envp);
	free_all(infos);
	close_std();
	signal_status(1);
	exit(EXIT_FAILURE);
}

void	create_pids(int (*pipes)[2], char **envp, t_minishell *infos, int i)
{
	t_cmd	*tmp;
	pid_t	pids[512];

	tmp = infos->cmd;
	while (tmp)
	{
		signal_fork();
		pids[i] = fork();
		if (pids[i] == -1)
		{
			close_pipes(pipes, infos->cmd);
			free_close(infos);
			perror("minishell: fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			if (!children_process(pipes, i, tmp, infos))
			{
				free_close(infos);
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
	wait_and_close(infos, pids, infos->pipes);
}

void	start_program(char **envp, t_minishell *infos)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = infos->cmd;
	while (tmp && i < 512)
	{
		if (pipe(infos->pipes[i]) == -1)
		{
			close_pipes(infos->pipes, infos->cmd);
			perror("minishell");
			return ;
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	create_pids(infos->pipes, envp, infos, i);
}

int	ft_execute(t_minishell *infos)
{
	long long int	builtin;
	int	tmp_exit_code;
	
	if (!make_lstcmd(infos))
		return (0);
	infos->env_tab = lst_to_tab(infos->env);
	if (!infos->env_tab)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	builtin = only_builtin(infos);
	start_program(infos->env_tab, infos);
	ft_free_env(infos->env_tab);
	if (builtin != -2)
	{
		if (infos->exit_code == -1)
		{
			infos->exit_code = 1;
			return (1);
		}
		tmp_exit_code = infos->exit_code;
		free_all(infos);
		exit(tmp_exit_code);
	}
	return (1);
}
