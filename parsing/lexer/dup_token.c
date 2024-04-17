/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:22:24 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/17 17:22:59 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_token(char *line, int *i, t_env *env)
{
	int		j;
	int		len;
	char	*word;

	len = 0;
	while (line[len] && ((line[len] != ' ') && !(line[len] <= 13 
			&& line[len] >= 9)))
			len++;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	j = 0;
	while (line[j] && j < len)
	{
		word[j] =  line[j];
		j++;
	}
	*i = *i + j;
	return (word);
}