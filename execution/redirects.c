/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:47:06 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 18:52:42 by roguigna         ###   ########.fr       */
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
			return (1);
		}
	}
	else if (cmd->fd_out != -1)
	{
		cmd->fd_out = open(token->next->value, O_TRUNC | O_WRONLY
				| O_CREAT, 0644);
		if (cmd->fd_out == -1)
		{
			ft_puterrors(token->next->value);
			return (1);
		}
	}
	return (0);
}

static int	ft_redirect_type(t_token *token, t_cmd *cmd)
{
	if (token->token_type == REDIRECT_IN)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		cmd->fd_in = open(token->next->value, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
		{
			ft_puterrors(token->next->value);
			return (1);
		}
	}
	if (token->token_type == REDIRECT_OUT)
		return (redirect_out(token, cmd));
	if (token->token_type == HERE_DOC)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		cmd->fd_in = open(cmd->tmp_file, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
		{
			ft_puterrors(token->next->value);
			return (1);
		}
	}
	return (0);
}

int	ft_redirects(t_cmd *cmd, t_minishell *infos)
{
	t_token	*token;

	token = cmd->redir;
	while (token && token->token_type != PIPE)
	{
		if (token->token_type != WORD)
		{
			if (ft_redirect_type(token, cmd))
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
