/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:28:25 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/21 22:24:53 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(t_minishell *infos)
{
	t_env *tmp_env;

	tmp_env = infos->env;
	if (!ft_strcmp(infos->token->value, "cd"))
	{
		if (!infos->token->next)
		{
			 while (tmp_env->next)
			{
				if (!ft_strcmp(tmp_env->name, "HOME"))
				{
					break;
				}
				tmp_env = tmp_env->next;
			}
			if (chdir(tmp_env->value) != 0)
			{
				perror("minishell: cd: << HOME >> undefined\n");
				return ;
			}
				
		}
		else if (chdir(infos->token->next->value) != 0)
		{
			printf("%s\n", strerror(errno));
		}
	}
}

static int	check_env_home(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->name == "HOME")
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int check_is_path_valid(t_minishell *infos)
{
	// try to opendir
	// ENOENT : Le répertoire n'existe pas, ou name est une chaîne vide. return -1;
	// ENOTDIR : name n'est pas un répertoire return -2;
	return (0);
}