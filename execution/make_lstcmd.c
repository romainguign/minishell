/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:35:33 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/26 18:19:14 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redirects(t_token *token, t_cmd *cmd)
{
	if (token->token_type == REDIRECT_IN)
	{
		cmd->fd_in = open(token->next->value, O_APPEND | O_RDONLY,  0644);
		if (cmd->fd_in == -1)
			ft_puterrors(token->next->value);
	}
	if (token->token_type == REDIRECT_OUT)
	{
		if (token->value[1] == '>')
		{
			cmd->fd_out = open(token->next->value, O_APPEND | O_WRONLY | O_CREAT,  0644);
			if (cmd->fd_out == -1)
				ft_puterrors(token->next->value);
		}
		else
		{
			cmd->fd_out = open(token->next->value, O_TRUNC| O_WRONLY | O_CREAT,  0644);
			if (cmd->fd_out == -1)
				ft_puterrors(token->next->value);
		}
	}
	if (token->token_type == HERE_DOC)
		return (here_doc(token, cmd, token->next->value));
	return (1);
}

static int	ft_cmdsize(t_token *token)
{
	int		len;
	t_token *tmp;

	len = 0;
	tmp = token;
	while (tmp && tmp->token_type != PIPE)
	{
		if (tmp->token_type != WORD)
			tmp = tmp->next;
		else
			len++;
		tmp = tmp->next;
	}
	return (len);
}

static t_cmd	*ft_newcmd(t_token *token, t_token *pipe)
{
	t_cmd	*cmd;
	int		i;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->cmd = ft_calloc(sizeof(char *), ft_cmdsize(pipe) + 1);
	if (!cmd->cmd)
		return (0);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	i = 0;
	while (pipe && pipe != token->next && pipe->token_type != PIPE)
	{
		if (pipe->token_type != WORD)
		{
			ft_redirects(pipe, cmd);
			pipe = pipe->next;
		}
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
