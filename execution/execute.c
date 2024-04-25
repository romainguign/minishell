/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:58:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/24 16:39:33 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execution(char **cmd, char **envp, t_minishell *infos)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		free_all(infos);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}
// void	create_pids(int (*pipes)[2], char **envp, t_pipex *pipex, int i)
// {
// 	pid_t	pids[512];

// 	while (pipex->cmd[i])
// 	{
// 		pids[i] = fork();
// 		if (pids[i] == -1)
// 		{
// 			close_pipes(pipex, pipes, pipex->infile);
// 			free_all(pipex);
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pids[i] == 0)
// 		{
// 			children_process(pipes, i, pipex);
// 			if ((i != 0 || pipex->infile != -2)
// 				&& (pipex->cmd[i + 1] || pipex->outfile != -2))
// 				ft_execution(pipex->cmd[i], envp, pipex);
// 			free_all(pipex);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	wait_and_close(pipex, pids, pipes);
// }

// void	start_program(char **envp, t_minishell *pipex)
// {
// 	int	pipes[512][2];
// 	int	i;

// 	i = 0;
// 	while (pipex->cmd[i])
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			close_pipes(pipex, pipes, pipex->infile);
// 			free_all(pipex);
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	create_pids(pipes, envp, pipex, i);
// }

int	ft_execute(t_minishell *infos)
{
	if (!make_lstcmd(infos))
		return (0);
	return (1);
}
