/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:55:17 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/15 14:51:25 by roguigna         ###   ########.fr       */
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
	struct s_token		*next;
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
char	*ft_strdup(char *s);
//free_all :
void	free_tab(void **tab);
void	free_all(t_minishell *infos);

/*--------------------------------- parsing ---------------------------------*/
//env :
char	**get_env(char **envp);

//tokenizer :
int				tokenizer(t_minishell *infos);
void			ft_tokenclear(t_token **lst, void (*del)(void*));
t_token_type	get_token_type(char *value);
//parser :

#endif