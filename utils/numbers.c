/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:25:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/24 12:59:00 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_nbr(long int n)
{
	int	len;

	len = 0;
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	int			negative;
	long int	nbr;
	char		str_nbr[12];
	char		*returned_number;

	nbr = (long int)n;
	negative = 0;
	if (nbr < 0)
	{
		negative = 1;
		nbr *= -1;
	}
	len = ft_len_nbr(nbr) + negative;
	if (negative == 1)
		str_nbr[0] = '-';
	str_nbr[len] = '\0';
	while (len - 1 >= negative)
	{
		str_nbr[len - 1] = nbr % 10 + 48;
		nbr = nbr / 10;
		len--;
	}
	returned_number = ft_strdup(str_nbr);
	return (returned_number);
}

long long int	ft_atoll(const char *str)
{
	long long	i;
	long long	sign;
	long long	somme;

	somme = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] - '0' >= 0 && str[i] - '0' <= 9))
	{
		somme = somme * 10 + str[i] - '0';
		i++;
	}
	return (somme * sign);
}