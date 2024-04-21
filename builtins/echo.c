/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:52 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/19 22:03:38 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_token *token)
{
	t_token *tmp;
	
	tmp = token;
	if (!ft_strcmp(tmp->value, "echo"))
	{
		if (tmp->next)
		{
			if(!ft_strcmp(token->next->value, "-n"))
			{
				printf("");
			}
			else
			{
				while (token->next)
				{
					
				}
			}
		}
	}
}