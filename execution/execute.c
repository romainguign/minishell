/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/11 13:01:41 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execution(char **cmd, char **envp, t_minishell *infos)
{
	exec_builtin(cmd, infos);
	if (cmd[0])
	{
		execve(cmd[0], cmd, envp);
		if (cmd[0][0] == '\0' && access(cmd[0], F_OK) == -1)
		{
			access_error(cmd[0], ": command not found\n");
			ft_free_env(envp);
			free_all(infos);
			close_std();
			signal_status(1);
			exit (127);
		}
		ft_puterrors(cmd[0]);
	}
	ft_free_env(envp);
	free_all(infos);
	close_std();
	signal_status(1);
	exit(EXIT_FAILURE);
}

void	fork_process(t_minishell *infos, t_cmd *cmd, int i, char **envp)
{
	if (!children_process(infos->pipes, i, cmd, infos))
	{
		free_close(infos);
		exit(EXIT_FAILURE);
	}
	check_access(cmd->redir);
	check_cmds(cmd, infos->env, infos);
	ft_execution(cmd->cmd, envp, infos);
	close_fds(infos->cmd);
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
			close_pipes(pipes);
			free_close(infos);
			perror("minishell: fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
			fork_process(infos, tmp, i, envp);
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
	while (tmp && i < 509)
	{
		if (pipe(infos->pipes[i]) == -1)
		{
			close_pipes(infos->pipes);
			perror("minishell");
			return ;
		}
		tmp = tmp->next;
		i++;
	}
	if (i == 509)
	{
		close_pipes(infos->pipes);
		ft_putstr_fd("minishell: Too many command\n", 2);
		return ;
	}
	i = 0;
	create_pids(infos->pipes, envp, infos, i);
}

int	ft_execute(t_minishell *infos)
{
	long long int	builtin;
	int				tmp_exit_code;

	if (!make_lstcmd(infos))
		return (0);
	infos->env_tab = lst_to_tab(infos->env);
	if (!infos->env_tab)
		return (0);
	builtin = only_builtin(infos);
	start_program(infos->env_tab, infos);
	ft_free_env(infos->env_tab);
	if (builtin != -2 && !ft_strcmp(infos->cmd->cmd[0], "exit"))
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
