/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:15:13 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/07 13:38:18 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterrors(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	perror(s);
}

void	syntax_errors(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, &c, 1);
	write(2, "\'", 1);
}