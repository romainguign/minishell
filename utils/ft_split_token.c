/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:46:59 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/11 13:11:30 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	split_chain(int nbwords, char *charset, char *str, char **strs)
{
	int	index;
	int	size_word;

	index = 0;
	size_word = 0;
	while (index < nbwords)
	{
		while (ft_is_sep(charset, *str) || size_word > 0)
		{
			str++;
			size_word--;
		}
		size_word = ft_get_size_word(str, charset);
		strs[index] = ft_calloc(sizeof(char), (size_word + 1));
		if (!strs[index])
		{
			free_tab((void **)strs);
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
		ft_strlcpy(strs[index], str, size_word + 1);
		index++;
	}
	strs[index] = 0;
	return (1);
}

char	**ft_split_token(char *str, char *charset)
{
	char	**strs;
	int		nbwords;

	nbwords = ft_get_number_of_word(str, charset);
	if (!str || !charset)
		return (NULL);
	strs = ft_calloc(sizeof(char *), (ft_get_number_of_word(str, charset) + 2));
	if (strs == NULL)
		return (NULL);
	if (!split_chain(nbwords, charset, str, strs))
		return (0);
	return (strs);
}
