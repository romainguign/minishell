/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:22:39 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/16 14:15:17 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 2);
		rl_redisplay();
	}
	return ;
}

void	signal_handler(void)
{
	struct sigaction	signal_int;
	struct sigaction	signal_quit;

	ft_bzero(&signal_int, sizeof(signal_int));
	ft_bzero(&signal_quit, sizeof(signal_quit));
	signal_int.sa_handler = &sig_handler;
	signal_quit.sa_handler = &sig_handler;
	if (sigaction(SIGINT, &signal_int, NULL) < 0)
	{
		perror("Error: Signal error");
		return ;
	}
	if (sigaction(SIGQUIT, &signal_quit, NULL) < 0)
	{
		perror("Error: Signal error");
		return ;
	}
}
