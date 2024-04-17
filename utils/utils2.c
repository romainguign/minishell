/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:48:53 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/17 19:35:24 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	i = 0;
	ptr_s1 = (const unsigned char *)s1;
	ptr_s2 = (const unsigned char *)s2;
	if (!s1 && s2)
		return (s2[0]);
	if (s1 && !s2)
		return (s1[0]);
	if (!s1 && !s2)
		return (0);
	while (ptr_s1[i] && ptr_s2[i] && ptr_s1[i] == ptr_s2[i])
		i++;
	return (ptr_s1[i] - ptr_s2[i]);
}

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t			index;
	unsigned char	*s1;
	unsigned char	*s2;

	index = 0;
	s1 = (unsigned char *) first;
	s2 = (unsigned char *) second;
	while ((s1[index] || s2[index]) && index < length)
	{
		if (s1[index] != s2[index])
			return ((int) s1[index] - (int) s2[index]);
		index++;
	}
	return (0);
}