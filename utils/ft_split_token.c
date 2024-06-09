/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:46:59 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/09 15:01:04 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_sep(char *charset, char charc)
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

static int	ft_get_number_of_word(char *str, char *charset)
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

static int	ft_get_size_word(char *str, char *charset)
{
	int	index;

	index = 0;
	while (!ft_is_sep(charset, str[index]) && str[index] != '\0')
	{
		index++;
	}
	return (index);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 1;
	len = 0;
	while (i < size && src[i - 1])
	{
		dst[i - 1] = src[i - 1];
		i++;
	}
	if (size > 0)
		dst[i - 1] = '\0';
	while (src[len])
		len++;
	return (len);
}

char	**ft_split_token(char *str, char *charset)
{
	int		index;
	int		size_word;
	char	**strs;
	int		nbwords;

	nbwords = ft_get_number_of_word(str, charset);
	index = -1;
	size_word = 0;
	if (!str || !charset)
		return (NULL);
	strs = ft_calloc(sizeof(char *), (ft_get_number_of_word(str, charset) + 2));
	if (strs == NULL)
		return (NULL);
	while (++index < nbwords)
	{
		while (ft_is_sep(charset, *str) || size_word > 0)
		{
			str++;
			size_word--;
		}
		size_word = ft_get_size_word(str, charset);
		strs[index] = malloc(sizeof(char) * (size_word + 1));
		ft_strlcpy(strs[index], str, size_word + 1);
	}
	strs[index] = 0;
	return (strs);
}
