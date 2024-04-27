/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:02:15 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/26 17:38:23 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_word(const char *str, char c)
{
	int	count;
	int	i;

	i = 1;
	count = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i - 1] != c && str[i] == c)
			count++;
		i++;
	}
	if (!str[i] && str[i - 1] != c)
		count++;
	return (count);
}

static char	*ft_strdup_split(const char *src, int len, int i)
{
	char	*copy;
	int		j;

	j = 0;
	copy = malloc(sizeof(char) * (len - i) + 1);
	if (copy == NULL)
		return (0);
	while (src[i] && i < len)
	{
		copy[j] = src[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

static char	**ft_free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (tab);
}

static char	**ft_copy_words(char **strs, const char *str, char c, int words_nbr)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (i < words_nbr)
	{
		len = j;
		while (str[len] != c && str[len])
			len++;
		if (len != 0 && str[len - 1] != c)
		{
			strs[i] = ft_strdup_split(str, len, j);
			if (!strs[i])
				return (ft_free_tab(strs, words_nbr + 1));
			i++;
		}
		j = len;
		j++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words_nbr;

	words_nbr = ft_count_word(s, c);
	strs = malloc(sizeof(char *) * (words_nbr + 1));
	if (!strs)
		return (0);
	strs[words_nbr] = 0;
	if (!strs)
		return (0);
	strs = ft_copy_words(strs, s, c, words_nbr);
	return (strs);
}
