/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:08:11 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/11 13:11:44 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_sep(char *charset, char charc)
{
	int	index;

	index = 0;
	while (charset[index])
	{
		if (charset[index] == charc)
		{
			return (1);
		}
		index++;
	}
	return (0);
}

int	ft_get_number_of_word(char *str, char *charset)
{
	int	index;
	int	count;

	index = 1;
	count = 0;
	if (str == NULL)
		return (0);
	if (!ft_is_sep(charset, str[0]))
		count++;
	while (str[index] && str)
	{
		if (!ft_is_sep(charset, str[index])
			&& ft_is_sep(charset, str[index - 1]))
		{
			count++;
		}
		index++;
	}
	return (count);
}
