/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:47:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/18 15:23:59 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *value)
{
	if (!ft_strcmp("<<", value))
		return (HERE_DOC);
	else if (!ft_strcmp("<", value))
		return (REDIRECT_IN);
	else if (!ft_strcmp(">", value) || !ft_strcmp(">>", value))
		return (REDIRECT_OUT);
	else if (!ft_strcmp("|", value))
		return (PIPE);
	else
		return (WORD);
}
