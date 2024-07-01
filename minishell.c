/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:01:18 by roguigna          #+#    #+#             */
/*   Updated: 2024/07/01 13:25:38 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

static int	exec_line(t_minishell *infos)
{
	int	result;

	result = tokenizer(infos);
	if (!result || result == -1)
		return (0);
	if (!env_tokenizer(infos))
		return (0);
	if (!check_token(infos))
		return (0);
	ft_execute(infos);
	ft_tokenclear(&infos->token, free);
	if (infos->cmd)
		ft_cmdsclear(&infos->cmd, free);
	return (1);
}

static char	*no_autocomplete(const char *text, int state)
{
	(void)text;
	(void)state;
	return (NULL);
}

static void	check_tty(void)
{
	if (!isatty(STDIN_FILENO))
	{
		rl_completion_entry_function = &no_autocomplete;
		rl_attempted_completion_over = 1;
	}
}

static int	minishell_loop(t_minishell *infos)
{
	char	*pwd;

	check_tty();
	while (1)
	{
		pwd = get_pwd();
		if (!pwd)
			return (0);
		infos->line = readline(pwd);
		free(pwd);
		check_received_signal(infos);
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
	g_exit_code = 0;
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
	return (exit_code);
}
