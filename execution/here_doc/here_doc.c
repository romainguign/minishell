/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:39:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/25 14:14:44 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_doc(char *s1, char *s2)
{
	size_t			i;
	size_t			str_len;
	char			*str;

	i = -1;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
		s2 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (0);
	str_len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = ft_calloc(sizeof(char), (str_len + 1));
	if (str == 0)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	if (i != 0)
		str[i] = '\n';
	i++;
	free(s1);
	ft_strlcat(str, s2, str_len);
	return (str);
}

static char	*here_doc_loop(char *limiter)
{
	char	*doc;
	char	*line;

	doc = ft_calloc(1, sizeof(char));
	while (doc)
	{
		line = readline(">");
		if (!ft_strcmp(line, limiter) || line == NULL)
			break ;
		if (line)
		{
			add_history(line);
			doc = ft_strjoin_doc(doc, line);
			free(line);
		}
	}
	if (!doc)
		ft_putstr_fd(MALLOC_ERROR, 2);
	return (doc);
}

int	here_doc(t_token *token, t_cmd *cmd, char *limiter)
{
	char	*doc;

	if (!init_tmp_file(cmd, token))
		return (0);
	doc = here_doc_loop(limiter);
	if (!doc)
		return (0);
	ft_create_tmp_file(cmd->fd_in, doc, limiter, ft_strlen(limiter));
	free(doc);
	return (1);
}
