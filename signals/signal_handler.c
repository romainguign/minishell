/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:22:39 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/22 09:48:22 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("^C");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	signal_handler(int pid)
{
	struct sigaction	signal;
	struct sigaction	signalign;
	struct sigaction	signal_fork;
    sigemptyset(&signal.sa_mask);
	sigemptyset(&signalign.sa_mask);
	sigemptyset(&signal_fork.sa_mask);
	if (pid == 1)
	{
		signal.sa_flags = SA_RESTART;
		signalign.sa_flags = 0;
		signal.sa_handler = &sig_handler;
		signalign.sa_handler = SIG_IGN;
		if (sigaction(SIGINT, &signal, NULL) < 0)
		{
			perror("Error: Signal error");
			return ;
		}
		if (sigaction(SIGQUIT, &signalign, NULL) < 0)
		{
			perror("Error: Signal error");
			return ;
		}
	}
	else if (pid == 0)
	{
		signal_fork.sa_handler = SIG_DFL;
		signal_fork.sa_flags = SIGCHLD;
		if (sigaction(SIGINT, &signal_fork, NULL) < 0)
		{
			perror("Error: Signal error");
			return ;
		}
		if (sigaction(SIGQUIT, &signal_fork, NULL) < 0)
		{
			perror("Error: Signal error");
			return ;
		}
	}
}
