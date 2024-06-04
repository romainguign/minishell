/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:48:43 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/04 11:07:26 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_key(char *cmd)
{
	int i;
	
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] == '+')
			return (i);
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
	target->value = ft_realloc((void *)target->value, get_len_value(cmd));
	target->value = ft_memcpy(target->value, &cmd[i], get_len_value(cmd));
	free(key);
}

void	join_value(t_env **env, char *cmd)
{
	char	*key;
	t_env	*target;
	int i;
	int len_join;
	int	len_value;
	
	i = get_len_key(cmd) + 2;
	len_join = 0;
	key = ft_strldup(cmd, get_len_key(cmd));
	if (!key)
		return ;
	target = get_env_node((*env), key);
	len_value = ft_strlen(target->value);
	i += ft_strlen(target->value);
	while (cmd[i])
	{
		len_join++;
		i++;
	}
	i = get_len_key(cmd) + 2;
	if (cmd[i] != '\0')
		target->value = ft_strjoinfree(target->value, &cmd[i]);
	free(key);
}