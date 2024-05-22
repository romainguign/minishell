/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:35:33 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/15 15:39:15 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmdsize(t_token *token, int *len_redir)
{
	int		len;
	t_token	*tmp;

	len = 0;
	tmp = token;
	while (tmp && tmp->token_type != PIPE)
	{
		if (tmp->token_type != WORD)
			tmp = tmp->next;
		else
			len++;
		tmp = tmp->next;
		(*len_redir)++;
	}
	return (len);
}

static int	fill_cmd(t_cmd *cmd, t_token *token, t_token *pipe)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipe && pipe != token->next && pipe->token_type != PIPE)
	{
		if (pipe->token_type != WORD)
			pipe = pipe->next;
		else
		{
			cmd->cmd[i] = ft_strdup(pipe->value);
			if (!cmd->cmd[i])
			{
				ft_putstr_fd(MALLOC_ERROR, 2);
				return (0);
			}
			i++;
		}
		pipe = pipe->next;
	}
	return (1);
}

static t_cmd	*ft_newcmd(t_token *token, t_token *pipe)
{
	t_cmd	*cmd;
	int		len_redir;

	len_redir = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->cmd = ft_calloc(sizeof(char *), ft_cmdsize(pipe, &len_redir) + 1);
	if (!cmd->cmd)
		return (0);
	cmd->redir = pipe;
	if (!cmd->redir)
		return (0);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	if (!fill_cmd(cmd, token, pipe))
		return (0);
	return (cmd);
}

static int	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*e_last;

	if (!new)
		return (0);
	if (!(*cmd))
	{
		*cmd = new;
		return (1);
	}
	e_last = *cmd;
	while (e_last->next)
		e_last = e_last->next;
	e_last->next = new;
	return (1);
}

int	make_lstcmd(t_minishell *infos)
{
	t_token	*tmp;
	t_token	*pipe;
	int		i;

	tmp = infos->token;
	pipe = infos->token;
	i = 0;
	while (tmp)
	{
		if (tmp->next == NULL && tmp->token_type != WORD)
		{
			ft_tokenerror(tmp->token_type);
			return (1);
		}
		if (tmp->token_type == PIPE || tmp->next == NULL)
		{
			if (!ft_cmdadd_back(&infos->cmd, ft_newcmd(tmp, pipe)))
			{
				free_all(infos);
				return (0);
			}
			pipe = tmp->next;
		}
		tmp = tmp->next;
		i++;
	}
	return (1);
}
