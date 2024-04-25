/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:15:13 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/24 14:20:58 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterrors(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	perror(s);
}