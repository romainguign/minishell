/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:18:59 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/17 19:16:23 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, &s[i], ft_strlen(s));
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char				*array;

	if (nmemb != 0 && size != 0 && (nmemb * size) / size != nmemb)
		return (0);
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	array = malloc(size * nmemb);
	if (array == 0)
		return (0);
	ft_bzero(array, nmemb * size);
	return (array);
}

char	*ft_strdup(char *s)
{
	int		len_src;
	int		i;
	char	*copy;

	i = 0;
	len_src = ft_strlen(s);
	copy = malloc(sizeof(char) * (len_src + 1));
	if (copy == 0)
		return (0);
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
