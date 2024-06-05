/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:01:18 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/05 12:36:06 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_line(t_minishell *infos)
{
	int	result;

	result = tokenizer(infos);
	if (!result || result == -1 || !check_token(infos))
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
		free(pwd);
		if (!infos->line)
			return (0);
		signal_status(0);
		if (infos->line && infos->line[0] != '\0')
		{
			add_history(infos->line);
			exec_line(infos);
		}
		signal_status(1);
		free(infos->line);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*infos;
	int			exit_code;
	
	(void)argv;
	signal_status(1);
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
	minishell_loop(infos);
	exit_code = infos->exit_code;
	free_all(infos);
	ft_putstr_fd("exit\n", 1);
	close_std();
	return (exit_code);
}
