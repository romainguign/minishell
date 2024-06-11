/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimspaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:17:30 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/11 13:01:25 by roguigna         ###   ########.fr       */
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

static void	trim_cpy(char *str, char *trimmed)
{
	int		i;
	int		j;
	int		space;

	i = 0;
	j = 0;
	space = 0;
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
}

char	*ft_strtrim_spaces(char *str)
{
	char	*trimmed;

	if (!str)
		return (0);
	trimmed = ft_calloc(ft_strlen_space(str) + 1, sizeof(char));
	if (!trimmed)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	trim_cpy(str, trimmed);
	return (trimmed);
}
