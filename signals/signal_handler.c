/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:22:39 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/29 14:04:46 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signal)
{
	if (g_signal_receive == 0)
	{
		if (signal == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (g_signal_receive == 1)
	{
		if (signal == SIGINT)
		{
			printf("\n");
			g_signal_receive = 0;
			return ;
		}
		if (signal == SIGQUIT)
		{
			g_signal_receive = 0;
			return ;
		}
	}
	
	return ;
}

void	signal_handler(int pid)
{
	struct sigaction	signal;
	struct sigaction	signalign;
    sigemptyset(&signal.sa_mask);
	sigemptyset(&signalign.sa_mask);
	signal.sa_flags = SA_RESTART;
	signalign.sa_flags = 0;
	signal.sa_handler = &sig_handler;
	if (pid == 0)
		signalign.sa_handler = SIG_IGN;
	else if (pid == 1)
		signalign.sa_handler = &sig_handler;
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
