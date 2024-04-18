/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:28:25 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/18 15:45:48 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(t_minishell *infos)
{
	int i;

	i = 0;
	if (!ft_strcmp(infos->token->value, "cd"))
	{
		if (!infos->token->next)
		{
			// while (infos->env[i])
			// {
			// 	printf("%s\n",infos->env[i]);
			// 	i++;
			// }
		}
		else if (chdir(infos->token->next->value) != 0)
		{
			printf("%s\n", strerror(errno));
		}
	}
}