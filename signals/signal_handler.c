/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:22:39 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/16 10:14:28 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	signal_handler(void)
{
	struct sigaction	signal;

	ft_bzero(&signal, sizeof(signal));
	signal.sa_handler = &sigint_handler;
	if (sigaction(SIGINT, &signal, NULL) < 0)
	{
		perror("Error: Signal error");
		return ;
	}
}
