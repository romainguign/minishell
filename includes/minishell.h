/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:55:17 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/07 19:42:40 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <limits.h>
# include <termios.h>

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

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
	char				quote;
	struct s_token		*next;
	// struct s_token		*prev;
	t_token_type		token_type;
}	t_token;

typedef struct s_cmd
{
	char				*tmp_file;
	char				**cmd;
	int					fd_in;
	int					fd_out;
	int					exit;
	struct s_cmd		*next;
	t_token				*redir;
}	t_cmd;

typedef struct s_minishell
{
	char				*line;
	char				**env_tab;
	int					pipes[512][2];
	long long int		exit_code;
	t_env				*env;
	t_token				*token;
	t_cmd				*cmd;
}	t_minishell;

/*----------------------------- Errors messages -----------------------------*/
# define MALLOC_ERROR		"minishell: malloc: failed allocation memory\n"
# define BRACKET_ERROR		"minishell: unclosed bracket\n"
# define CD_ENV_HOME_ERROR	"minishell: cd: << HOME >> undefined\n"

# define BASE "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*---------------------------------- utils ----------------------------------*/

void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_realloc(void *ptr, size_t newsize);
void			ft_bzero(void *s, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *first, const char *second,
					size_t length);
int				ft_strlen(const char *str);
int				ft_tab_len(char **tab);
int				ft_lst_size_env(t_env *env);
char			**lst_to_tab_export(t_env *env);
int				is_space(char c);
int				no_space(char *value);
int				is_num(char c);
int				ft_isalnum(int c);
int				ft_len_nbr(long int n);
char			*ft_itoa(int n);
long long int	ft_atoll(const char *str);
char			*ft_strdup(char *s);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strldup(char *s, int len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoinfree(char *s1, char *s2);
char			*ft_strjoin_env(char *s1, char *s2);
char			*ft_strjoin_export(char *s1, char *s2);
char			**ft_split(char const *s, char c);
char			**ft_split_token(char *str, char *charset);
char			*get_pwd(t_env *env);
size_t			ft_strlcat(char *dst, const char *src, size_t size);

//free_all :
void			free_tab(void **tab);
void			free_all(t_minishell *infos);
void			free_close(t_minishell *infos);

/*--------------------------------- parsing ---------------------------------*/
//env :
int				get_env(char **envp, t_minishell *infos);
void			ft_free_env(char **env);
void			ft_envclear(t_env **lst, void (*del)(void*));
char			*bracket_env_name(char *line, int *len);
char			*no_bracket_env_name(char *line, int *len, char quote);
t_env			*ft_newenv(char *envp);
int				ft_envadd_back(t_env **env, t_env *new);
char			**lst_to_tab(t_env *env);

//tokenizer :
int				tokenizer(t_minishell *infos);
int				env_tokenizer(t_minishell *infos);
int				check_token(t_minishell *infos);
char			*dup_token(char *line, int *i, t_minishell *infos, t_token *token);
char			*strljoin_token(char *s1, char *s2, int len);
char			*find_dollar_value(char *line, t_minishell *infos, int *i, char quote);
char			*ft_strtrim_spaces(char *str);
char			*parse_redirect(char *line, int	*i);
void			ft_tokenclear(t_token **lst, void (*del)(void*));
t_token_type	get_token_type(char *value, t_token *token);

//parser :

/*--------------------------------- signals ---------------------------------*/
void 			signal_status(int state);
void			signal_fork();

/*--------------------------------- errors ----------------------------------*/
void			ft_puterrors(char *s);
void			syntax_errors(char c, t_minishell *infos);
void			ft_tokenerror(t_token_type type, t_minishell *infos);

/*--------------------------------- builtins --------------------------------*/
//pwd :
int				ft_pwd(char **cmd);

//cd :
int		ft_cd(t_minishell *infos, char **cmd, int fork);
t_env			*get_env_node(t_env *env, char *node);

//echo :
int				ft_echo(char **cmd);

//export :
int				ft_export(t_env *env, char **cmd, int fork);
int				is_wrong_identifier(char c);
int				is_input_correct(char *str);
void			new_env_element_key(char *cmd, t_env *env);
void			update_value(t_env **env, char *cmd);
void 			check_type_and_add(char *cmd, t_env *env);
int				get_len_key(char *cmd);
void			join_value(t_env **env, char *cmd);
t_env			*ft_newenv_export(char *envp);

//unset :
int				ft_unset(t_env *env, char **cmd);
int				is_env_key_exist(t_env *env, char *key);

//env :
int				ft_env(t_env *env);

//exit :
long long int				ft_exit(char **cmd, t_minishell *infos, int fork);

/*--------------------------------- execution -------------------------------*/
int				ft_execute(t_minishell *infos);
long long int	only_builtin(t_minishell *infos);
void			exec_builtin(char **cmd, t_minishell *infos);
int				make_lstcmd(t_minishell *infos);
int				check_cmds(t_cmd *cmds, t_env *env, t_minishell *infos);
int				check_access(t_token *redir);
int				ft_redirects(t_cmd *cmd, t_minishell *infos);
int				children_process(int (*pipes)[2], int i, t_cmd *cmd,
					t_minishell *infos);
void			ft_cmdsclear(t_cmd **lst, void (*del)(void*));
void			close_pipes(int (*pipes)[2], t_cmd *cmd);
void			wait_and_close(t_minishell *infos, pid_t *pids,
					int (*pipes)[2]);
void			close_std(void);
void			close_fds(t_cmd *cmd);

//here_doc :
int				here_doc(t_token *token, t_cmd *cmd, char *limiter, t_minishell *infos);
int				init_tmp_file(t_cmd *cmd, t_token *token);
char			*check_env_var(char quote, char *line, t_minishell *infos);
void			ft_create_tmp_file(int infile, char *doc, char *limiter,
					int len_limiter);

#endif