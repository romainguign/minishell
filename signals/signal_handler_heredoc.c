/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:37:00 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/11 19:44:19 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_received_signal(t_minishell *infos)
{
	if (g_exit_code == SIGINT)
	{
		g_exit_code = 0;
		infos->exit_code = 130;
	}
}

void	free_here_doc(t_minishell *infos, char *doc)
{
	static t_minishell	*ptr_infos;
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
