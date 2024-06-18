/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterrors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:15:13 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/18 15:04:28 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd_errors(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

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
	{
		ft_putstr_fd("minishell: syntax error near", 2);
		ft_putstr_fd(" unexpected token `newline'\n", 2);
	}
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
