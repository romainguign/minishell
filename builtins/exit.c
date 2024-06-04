/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:59:57 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/04 12:44:31 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_is_not_num(char *str)
{
	int i;
	
	i = 0;
	if (ft_strlen(str) == 1)
	{
		if (str[0] < '0' && str[0] > '9')
			return (1);
	}
	else
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		while (str[i])
		{
			if (str[i] >= '0' && str[i] <= '9')
				i++;
			else
				return (1);
			i++;
		}
	}
	return (0);
}

static void	print_exit_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("numeric argument required", 2);
	ft_putstr_fd("\n", 2);
}

int ft_exit(char **cmd, t_minishell *infos)
{
	int size_cmd;
	int tmp_exit_code;
	int nbr;

	size_cmd = ft_tab_len(cmd);
	tmp_exit_code = 0;
	nbr = 0;
	printf("exit\n");
	if (size_cmd > 2)
	{
		if (!ft_str_is_not_num(cmd[1]))
		{
			nbr = ft_atoll(cmd[1]);
			if (ft_len_nbr(nbr) > 19)
			{
				print_exit_error(cmd[1]);
				free_all(infos);
				free_tab((void **)cmd);
				exit(2);
			}
			else
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				return (1); 
			}
		}
		else if (ft_str_is_not_num(cmd[1]))
		{
			print_exit_error(cmd[1]);
			free_all(infos);
			free_tab((void **)cmd);
			exit(2);
		}
	}
	else
	{
		if (size_cmd == 2)
		{
			if (ft_str_is_not_num(cmd[1]))
			{
				print_exit_error(cmd[1]);
				free_tab((void **)cmd);
				free_all(infos);
				exit(2);
			}
			else
			{
				nbr = ft_atoll(cmd[1]);
				if (ft_len_nbr(nbr) > 19)
				{
					print_exit_error(cmd[1]);
					free_all(infos);
					free_tab((void **)cmd);
					exit(2);
				}
				else
				{
					free_all(infos);
					free_tab((void **)cmd);
					exit(nbr);
				}
			}
		}
		if (size_cmd == 1)
		{
			tmp_exit_code = infos->exit_code;
			free_all(infos);
			free_tab((void **)cmd);
			exit(tmp_exit_code);
			
		}
	}
	return (0);
}