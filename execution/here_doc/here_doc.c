/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:39:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 19:13:11 by roguigna         ###   ########.fr       */
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
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file \
	(wanted `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("')\n", 2);
}

static char	*here_doc_loop(char *limiter, char *doc,
								t_token *token, t_minishell *infos)
{
	char	*line;

	free_here_doc(infos, doc);
	while (doc)
	{
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
		free_here_doc(infos, doc);
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

int	here_doc_fork(t_token *token, t_cmd *cmd, char *limiter, t_minishell *infos)
{
	char	*doc;

	doc = ft_calloc(1, sizeof(char));
	if (!doc)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		exit (1);
	}
	signal_heredoc();
	doc = here_doc_loop(limiter, doc, token, infos);
	if (!doc)
		exit (0);
	if (cmd->fd_in > 0)
		close (cmd->fd_in);
	cmd->fd_in = open(cmd->tmp_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (cmd->fd_in == -1)
		ft_puterrors(token->next->value);
	ft_putstr_fd(doc, cmd->fd_in);
	close (cmd->fd_in);
	free(doc);
	ft_free_env(infos->env_tab);
	free_all_here_doc(infos);
	close_std();
	exit (0);
}

int	here_doc(t_token *token, t_cmd *cmd, char *limiter, t_minishell *infos)
{
	pid_t	here_doc_pid;
	int		status;

	if (!init_tmp_file(cmd))
		return (1);
	here_doc_pid = fork();
	if (here_doc_pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (here_doc_pid == 0)
		here_doc_fork(token, cmd, limiter, infos);
	if (waitpid(here_doc_pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		free_all(infos);
		exit(EXIT_FAILURE);
	}
	status = check_status(status, infos);
	return (status);
}
