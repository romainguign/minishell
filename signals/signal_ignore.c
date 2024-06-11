/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_ignore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:38:24 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/11 19:46:03 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_ignore(int sig)
{
	(void)sig;
}

void	signal_ignore(void)
{
	signal(SIGINT, &sig_ignore);
	signal(SIGQUIT, &sig_ignore);
}
