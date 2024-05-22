/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:01:18 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/21 15:26:13 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_line(t_minishell *infos)
{
	if (!tokenizer(infos))
		return (0);
	ft_pwd(infos);
	ft_cd(infos);
	ft_echo(infos->token);
	ft_export(infos->env, infos->token);
	ft_unset(infos->env, infos->token);
	//ft_env(infos->env);
	if (ft_execute(infos) == 0)
		return (0);
	ft_tokenclear(&infos->token, free);
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
		free(pwd);
		if (!ft_strcmp(infos->line, "exit") || infos->line == NULL)
			break ;
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
	rl_catch_signals = 0;
	(void)argv;
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
	signal_handler(1);
	minishell_loop(infos);
	free_all(infos);
	ft_putstr_fd("exit\n", 1);
	close_std();
	return (0);
}
