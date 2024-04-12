/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:55:17 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/12 18:56:43 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE,
	HERE_DOC
}	t_token_type;

typedef struct s_token
{
	char				*value;
	struct t_token_type	*next;
	t_token_type		token_type;
}	t_token;

typedef struct s_minishell
{
	char	*line;
	char	**env;
	t_token	*token;
}	t_minishell;

/*----------------------------- Errors messages -----------------------------*/
# define MALLOC_ERROR		"minishell: malloc: failed allocation memory\n"

/*---------------------------------- utils ----------------------------------*/
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
//free_all :
void	free_tab(void **tab);
void	free_all(t_minishell *infos);

/*--------------------------------- parsing ---------------------------------*/
char	**get_env(char **envp);
char	*ft_strdup(char *s);

#endif