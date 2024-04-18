/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:48:53 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/18 15:16:35 by roguigna         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t			i;
	size_t			str_len;
	char			*str;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		s2 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (0);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(sizeof(char), (str_len + 1));
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	ft_strlcat(str, s2, str_len);
	if (s2[0] == '\0')
		free(s2);
	return (str);
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
