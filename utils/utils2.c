/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:48:53 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/18 10:14:16 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strldup(char *s, int len)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc(sizeof(char) * (len + 1));
	if (copy == 0)
		return (0);
	while (s[i] && i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	total_len;
	size_t	i;

	i = 0;
	if ((dst == 0 || src == 0) && size == 0)
		return (0);
	len_dest = ft_strlen(dst);
	total_len = ft_strlen(src);
	if (len_dest > size)
		return (total_len + size);
	total_len += len_dest;
	while (len_dest + 1 < size && src[i])
	{
		dst[len_dest] = src[i];
		len_dest++;
		i++;
	}
	dst[len_dest] = '\0';
	return (total_len);
}

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

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	cursize;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = ft_calloc(newsize, sizeof(ptr));
	if (!newptr)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	ft_memcpy(ptr, newptr, cursize);
	free(ptr);
	return (newptr);
}
