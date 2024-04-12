/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:01:18 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/12 18:53:05 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_line(t_minishell *infos)
{
	infos->token = tokenizer(infos->line);
	if (!infos->token)
		return (0);
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

	argv[0][0] = '\0';
	if (argc > 1)
		return (1);
	infos = ft_calloc(1, sizeof(t_minishell));
	if (!infos)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (1);
	}
	infos->env = get_env(envp);
	if (!infos->env)
		return (1);
	minishell_loop(infos);
	free_all(infos);
	return (0);
}
