/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:01:18 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/25 13:47:07 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_line(t_minishell *infos)
{
	if (!tokenizer(infos))
		return (0);
	ft_pwd(infos);
	ft_cd(infos);
	ft_export(infos->env, infos->token);
	ft_tokenclear(&infos->token, free);
	return (1);
}

static int	minishell_loop(t_minishell *infos)
{
	while (1)
	{
		infos->line = readline("minishell > ");
		if (!ft_strcmp(infos->line, "exit") || infos->line == NULL)
			break ;
		if (infos->line)
		{
			add_history(infos->line);
			if (!exec_line(infos))
				break ;
		}
		free(infos->line);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*infos;

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
	signal_handler();
	minishell_loop(infos);
	free_all(infos);
	return (0);
}