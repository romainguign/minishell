/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:55:17 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/21 22:24:39 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//to prevent syntax error on sigaction ps: do not move it 
# define _XOPEN_SOURCE 700  

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <errno.h>

typedef enum e_token_type
{
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE,
	HERE_DOC
}	t_token_type;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_token
{
	char				*value;
	struct s_token		*next;
	t_token_type		token_type;
}	t_token;

typedef struct s_minishell
{
	char	*line;
	t_env	*env;
	t_token	*token;
}	t_minishell;

/*----------------------------- Errors messages -----------------------------*/
# define MALLOC_ERROR		"minishell: malloc: failed allocation memory\n"
# define BRACKET_ERROR		"minishell: unclosed bracket\n"

/*---------------------------------- utils ----------------------------------*/

void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strcmp(const char *s1, const char *s2);
int		    	ft_strncmp(const char *first, const char *second, size_t length);
int				ft_strlen(const char *str);
int				is_space(char c);
int				ft_isalnum(int c);
char			*ft_strdup(char *s);
char			*ft_strldup(char *s, int len);
char			*ft_strjoin(char *s1, char *s2);
void			ft_bzero(void *s, size_t n);

//free_all :
void			free_tab(void **tab);
void			free_all(t_minishell *infos);

/*--------------------------------- parsing ---------------------------------*/
//env :
int				get_env(char **envp, t_minishell *infos);
void			ft_envclear(t_env **lst, void (*del)(void*));
char			*bracket_env_name(char *line, int *len);
char			*no_bracket_env_name(char *line, int *len);

//tokenizer :
int				tokenizer(t_minishell *infos);
char			*dup_token(char *line, int *i, t_env *env);
void			ft_tokenclear(t_token **lst, void (*del)(void*));
t_token_type	get_token_type(char *value);

//parser :

/*--------------------------------- signals ---------------------------------*/
void 			signal_handler(void);

/*--------------------------------- builtins ---------------------------------*/
//pwd :
void			ft_pwd(t_minishell *infos);

//cd :
void			ft_cd(t_minishell *infos);

//echo :
void			ft_echo(t_token *token);

#endif