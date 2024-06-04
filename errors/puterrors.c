/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:15:13 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/04 13:02:10 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterrors(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	perror(s);
}

void	ft_tokenerror(t_token_type type, t_minishell *infos)
{
	if (type == PIPE)
		syntax_errors('|', infos);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	infos->exit_code = 2;
}

void	syntax_errors(char c, t_minishell *infos)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, &c, 1);
	write(2, "\'\n", 2);
	infos->exit_code = 2;
}