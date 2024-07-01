/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:59:13 by roguigna          #+#    #+#             */
/*   Updated: 2024/07/01 11:19:46 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_join(char **s1, char **s2, int *alloc)
{
	if (!*s1)
		*s1 = ft_calloc(1, sizeof(char));
	if (!*s2)
	{
		*s2 = ft_calloc(1, sizeof(char));
		*alloc = 1;
	}
	if (!s1 || !s2)
	{
		if (s1)
			free (s1);
		if (s2)
			free (s2);
		return (0);
	}
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t			i;
	size_t			str_len;
	int				alloc;
	char			*str;

	i = 0;
	alloc = 0;
	if (!init_join(&s1, &s2, &alloc))
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
	ft_strlcat(str, s2, str_len);
	if (alloc == 1)
		free(s2);
	return (str);
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	size_t			i;
	size_t			str_len;
	char			*str;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		return (ft_strdup(s1));
	if (!s1 || !s2)
		return (0);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = ft_calloc(sizeof(char), (str_len + 1));
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '=';
	ft_strlcat(str, s2, str_len);
	return (str);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	size_t			i;
	size_t			str_len;
	int				alloc;
	char			*str;

	i = 0;
	alloc = 0;
	if (!init_join(&s1, &s2, &alloc))
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
	if (s2[0] == '\0' && alloc == 1)
		free(s2);
	return (str);
}

char	*ft_strjoin_export(char *s1, char *s2)
{
	size_t			i;
	size_t			str_len;
	char			*str;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		return (ft_strdup(s1));
	if (!s1 || !s2)
		return (0);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 3;
	str = ft_calloc(sizeof(char), (str_len + 1));
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '=';
	str[i] = '"';
	ft_strlcat(str, s2, str_len);
	str[str_len - 1] = '"';
	return (str);
}
