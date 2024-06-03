/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:48:43 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/03 11:13:08 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_key(char *cmd)
{
	int i;
	
	i = 0;
	while (cmd[i] != '=')
	{
		i++;
	}
	return (i);
}

static int get_len_value(char *cmd)
{
	int	i;
	int j;
	
	i = 0;
	j = get_len_key(cmd) + 1;
	while (cmd[j])
	{
		i++;
		j++;
	}
	return (i);
}

void	new_element_env(char *cmd, t_env *env)
{
	(void) env;
	// t_env	*new_element;
	// char	*key;
	// char 	*value;
	// int		len_key;
	// int		len_value;
	// len_key = get_len_key(cmd);
	// printf("len key = %d\n", len_key);
	// len_value = get_len_value(cmd);
	// printf("len value = %d\n", len_value);
}