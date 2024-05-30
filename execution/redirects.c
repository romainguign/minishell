/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:47:06 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/30 13:36:48 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_out(t_token *token, t_cmd *cmd)
{
	if (cmd->fd_out > 1)
		close (cmd->fd_out);
	if (token->value[1] == '>')
	{
		cmd->fd_out = open(token->next->value, O_APPEND | O_WRONLY
				| O_CREAT, 0644);
		if (cmd->fd_out == -1)
		{
			ft_puterrors(token->next->value);
			return (0);
		}
	}
	else if (cmd->fd_out != -1)
	{
		cmd->fd_out = open(token->next->value, O_TRUNC | O_WRONLY
				| O_CREAT, 0644);
		if (cmd->fd_out == -1)
		{
			ft_puterrors(token->next->value);
			return (0);
		}
	}
	return (1);
}

static int	ft_redirect_type(t_token *token, t_cmd *cmd, t_minishell *infos)
{
	if (token->token_type == REDIRECT_IN)
	{
		if (cmd->tmp_file)
		{
			if (access(cmd->tmp_file, F_OK | R_OK | W_OK) == 0)
				unlink(cmd->tmp_file);
			free(cmd->tmp_file);
			cmd->tmp_file = NULL;
		}
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		cmd->fd_in = open(token->next->value, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
		{
			ft_puterrors(token->next->value);
			return (0);
		}
	}
	if (token->token_type == REDIRECT_OUT)
		return (redirect_out(token, cmd));
	if (token->token_type == HERE_DOC)
		return (here_doc(token, cmd, token->next->value, infos));
	return (1);
}

int	ft_redirects(t_cmd *cmd, t_minishell *infos)
{
	t_token	*token;

	token = cmd->redir;
	while (token && token->token_type != PIPE)
	{
		if (token->token_type != WORD)
		{
			if (ft_redirect_type(token, cmd, infos) == 0)
			{
				free_close(infos);
				exit(1);
			}
			token = token->next;
		}
		token = token->next;
	}
	return (1);
}
