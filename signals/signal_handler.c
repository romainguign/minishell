/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:22:39 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/11 13:27:38 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_ignore(int sig)
{
	(void) sig;
}

static void	sig_handler_fork(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_exit_code = SIGINT;
		return ;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_exit_code = SIGQUIT;
		return ;
	}
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = SIGINT;
	}
}

void	signal_status(int state)
{
	if (state)
	{
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, &sig_ignore);
		signal(SIGQUIT, &sig_ignore);
	}
}

void	signal_fork(void)
{
	signal(SIGINT, &sig_handler_fork);
	signal(SIGQUIT, &sig_handler_fork);
}
