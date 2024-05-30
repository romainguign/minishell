/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:01:18 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/30 13:36:14 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_receive;

static int	exec_line(t_minishell *infos)
{
	int	result;

	result = tokenizer(infos);
	if (!result || result == -1)
		return (0);
	ft_execute(infos);
	ft_tokenclear(&infos->token, free);
	if (infos->cmd)
		ft_cmdsclear(&infos->cmd, free);
	return (1);
}

static int	minishell_loop(t_minishell *infos)
{
	char	*pwd;

	while (1)
	{
		pwd = get_pwd(infos->env);
		if (!pwd)
			return (0);
		infos->line = readline(pwd);
		if (!infos->line)
            return (0);
		free(pwd);
		if (!infos->line)
			return (0);
		if (infos->line && infos->line[0] != '\0')
		{
			add_history(infos->line);
			exec_line(infos);
		}
		free(infos->line);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*infos;
	int			exit_code;
	(void)argv;
	
	g_signal_receive = 0;
	if (argc > 1)
		return (1);
	infos = ft_calloc(1, sizeof(t_minishell));
	if (!infos)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (1);
	}
	if (!get_env(envp, infos))
	{
		free_all(infos);
		return (1);
	}
	signal_handler(0);
	minishell_loop(infos);
	exit_code = infos->exit_code;
	free_all(infos);
	ft_putstr_fd("exit\n", 1);
	close_std();
	return (exit_code);
}
