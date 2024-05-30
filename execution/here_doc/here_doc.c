/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:39:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/29 14:12:26 by brguicho         ###   ########.fr       */
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

static void	eof_warning(char *s)
{
	ft_putstr_fd("pipex: warning: here-document delimited by end-of-file \
	(wanted `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("')\n", 2);
}

static char	*here_doc_loop(char *limiter, char *doc,
							t_token *token, t_minishell *infos)
{
	char	*line;

	while (doc)
	{
		g_signal_receive = 1;
		signal_handler(1);
		line = readline(">");
		if (!ft_strcmp(line, limiter) || line == NULL)
			break ;
		line = check_env_var(token->next->quote, line, infos);
		if (line)
		{
			add_history(line);
			doc = ft_strjoin_doc(doc, line);
			free(line);
		}
	}
	if (!line)
		eof_warning(limiter);
	else
		free(line);
	doc = ft_strjoinfree(doc, "\n");
	if (!doc)
		ft_putstr_fd(MALLOC_ERROR, 2);
	return (doc);
}

int	here_doc(t_token *token, t_cmd *cmd, char *limiter, t_minishell *infos)
{
	char	*doc;

	if (!init_tmp_file(cmd, token))
		return (0);
	doc = ft_calloc(1, sizeof(char));
	if (!doc)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	doc = here_doc_loop(limiter, doc, token, infos);
	if (!doc)
		return (0);
	ft_putstr_fd(doc, cmd->fd_in);
	close (cmd->fd_in);
	cmd->fd_in = open(cmd->tmp_file, O_RDONLY, 0777);
	if (cmd->fd_in == -1)
		ft_puterrors(token->next->value);
	free(doc);
	return (1);
}
