/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:54:37 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/22 09:55:16 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}