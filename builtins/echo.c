/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:36:52 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/20 14:09:17 by brguicho         ###   ########.fr       */
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
				tmp = tmp->next;
				if (!tmp->next)
				{
					printf("");
					return ;
				}
				else
				{
					while (tmp)
					{
						if (tmp->next != NULL)
							printf("%s ", tmp->value);
						else
							printf("%s", tmp->value);
						tmp = tmp->next;
					}
					return ;
				}
			}
			else
			{
				tmp = tmp->next;
				while (tmp)
				{
					if (tmp->next != NULL)
					{
						printf("%s ", tmp->value);
					}
					else
					
						printf("%s\n", tmp->value);
					tmp = tmp->next;
				}
				return ;
			}
		}
	}
}