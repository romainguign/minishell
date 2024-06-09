/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimspaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:49:03 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/09 15:03:47 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_space(char *str)
{
	int	space;
	int	i;
	int	len;

	i = 0;
	space = 0;
	len = 0;
	while (str[i])
	{
		space = is_space(str[i]);
		if (space == 0 || (i > 0 && space == 1 && !is_space(str[i - 1])))
			len++;
		i++;
	}
	return (len);
}

char	*ft_strtrim_spaces(char *str)
{
	char	*trimmed;
	int		i;
	int		j;
	int		space;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	space = 0;
	trimmed = ft_calloc(ft_strlen_space(str) + 1, sizeof(char));
	if (!trimmed)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	while (str[i])
	{
		space = is_space(str[i]);
		if (space == 0 || (i > 0 && space == 1 && !is_space(str[i - 1])))
		{
			trimmed[j] = str[i];
			if (space == 1)
				trimmed[j] = ' ';
			j++;
		}
		i++;
	}
	return (trimmed);
}
