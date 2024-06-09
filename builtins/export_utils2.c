/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:48:43 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/09 15:32:51 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_key(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] == '+')
			return (i);
		i++;
	}
	return (i);
}

static int	get_len_value(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = get_len_key(cmd) + 1;
	while (cmd[j])
	{
		i++;
		j++;
	}
	return (i);
}

void	update_value(t_env **env, char *cmd)
{
	char	*key;
	t_env	*target;
	int		i;

	i = get_len_key(cmd) + 1;
	key = ft_strldup(cmd, get_len_key(cmd));
	if (!key)
		return ;
	target = get_env_node((*env), key);
	free(target->value);
	target->value = ft_calloc(sizeof(char), get_len_value((cmd)) + 1);
	if (!target->value)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return ;
	}
	target->value = ft_memcpy(target->value, &cmd[i], get_len_value(cmd));
	free(key);
}

void	join_value(t_env **env, char *cmd)
{
	char	*key;
	t_env	*target;
	int		i;
	int		len_join;

	i = get_len_key(cmd) + 2;
	len_join = 0;
	key = ft_strldup(cmd, get_len_key(cmd));
	if (!key)
		return ;
	target = get_env_node((*env), key);
	target->value = ft_strjoinfree(target->value, &cmd[i]);
	if (!target->value)
		return ;
	free(key);
}
