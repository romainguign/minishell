/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:22:39 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/10 13:27:32 by roguigna         ###   ########.fr       */
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
		return ;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
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

void	free_here_doc(t_minishell *infos, char *doc)
{
	static t_minishell *ptr_infos;
	static char			*ptr_doc;

	if (infos)
	{
		ptr_infos = infos;
		if (doc)
			ptr_doc = doc;
	}
	else
	{
		free_close(ptr_infos);
		free(ptr_doc);
	}
}

static void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		free_here_doc(NULL, NULL);
		exit(130);
	}
}

void	signal_heredoc(void)
{
	signal(SIGINT, &sig_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}