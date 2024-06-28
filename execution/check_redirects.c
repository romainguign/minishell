/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:58:59 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 19:10:32 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_files(t_cmd *cmd, t_token *redir, t_minishell *infos)
{
	int	result;

	if (redir->token_type == HERE_DOC)
	{
		result = here_doc(redir, cmd, redir->next->value, infos);
		return (result);
	}
	return (0);
}

static int	redirect_loop(t_token *redir, t_cmd *cmd, t_minishell *infos)
{
	int	exit_code;

	while (redir && redir->token_type != PIPE)
	{
		if (redir->token_type != WORD)
		{
			exit_code = check_files(cmd, redir, infos);
			if (exit_code > 0)
				return (exit_code);
			redir = redir->next;
		}
		if (redir)
			redir = redir->next;
	}
	return (0);
}

int	check_redirections(t_minishell *infos)
{
	t_cmd	*cmd;
	t_token	*redir;
	int		exit_code;

	cmd = infos->cmd;
	exit_code = 0;
	while (cmd)
	{
		redir = cmd->redir;
		exit_code = redirect_loop(redir, cmd, infos);
		if (exit_code > 0)
		{
			infos->exit_code = exit_code;
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
