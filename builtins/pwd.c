/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:46:29 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/25 14:21:16 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_minishell *infos)
{
	char *path;

	path = NULL;
	if (!ft_strcmp(infos->token->value, "pwd"))
	{
		path = getcwd(path, 0);
		printf("%s\n", path);
	}
}
