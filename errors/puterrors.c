/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:15:13 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/10 20:04:52 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterrors(char *s)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: ", s);
	if (!error_msg)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return ;
	}
	perror(error_msg);
	free (error_msg);
}

void	ft_tokenerror(t_token_type type, t_minishell *infos)
{
	if (type == PIPE)
		syntax_errors('|', infos);
	else
		ft_putstr_fd("minishell: syntax error near \
						unexpected token `newline'\n", 2);
	infos->exit_code = 2;
}

void	syntax_errors(char c, t_minishell *infos)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, &c, 1);
	write(2, "\'\n", 2);
	infos->exit_code = 2;
}

char	*error_code_ascii(int *len, t_minishell *infos)
{
	char	*name;

	name = NULL;
	name = ft_itoa(infos->exit_code);
	*len += 1;
	if (!name)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	return (name);
}
