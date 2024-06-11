/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:59:57 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/11 17:58:14 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_is_not_num(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_space(str[i]))
		i++;
	if (ft_strlen(&str[i]) == 1)
	{
		if (str[0] < '0' || str[0] > '9')
			return (1);
	}
	else
	{
		if (str[0 + i] == '-' || str[0 + i] == '+')
			i++;
		while (str[j + i])
		{
			if (str[j + i] >= '0' && str[j + i] <= '9')
				j++;
			else
				return (1);
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

static int	check_overflow(char *nbr, char sign)
{
	char	*max;
	int		i;

	max = ft_strdup("9223372036854775807");
	i = 0;
	if (!max)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	if (sign == '-')
		max[18] = '8';
	while (is_num(nbr[i]))
	{
		if (nbr[i] > max[i])
			return (0);
		i++;
	}
	free(max);
	return (1);
}

static int	check_max(char *nbr)
{
	int		i;
	int		j;
	char	sign;

	i = 0;
	j = 0;
	sign = '\0';
	if (nbr[0] == '-' || nbr[0] == '+')
	{
		sign = nbr[0];
		j++;
	}
	while (is_num(nbr[i + j]))
		i++;
	if (i > 19 || (i == 19 && !check_overflow(&nbr[j], sign)))
		return (0);
	return (1);
}

long long int	ft_exit(char **cmd, t_minishell *infos, int fork)
{
	int	nbr;

	if (!cmd[1])
		return (infos->exit_code);
	if (ft_str_is_not_num(cmd[1]) || !check_max(cmd[1]))
	{
		if (fork == 0)
			print_exit_error(cmd[1]);
		return (2);
	}
	nbr = ft_atoll(cmd[1]);
	if (cmd[2])
	{
		if (fork == 0)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		return (-1);
	}
	if (nbr == -1 || nbr == -2)
		return (256 + nbr);
	return (nbr);
}
