# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 15:00:46 by roguigna          #+#    #+#              #
#    Updated: 2024/04/27 15:06:06 by roguigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= cc

CFLAGS 			= -Wall -Wextra -g3  #-Werror 

READLINE_FLAG	= -lreadline

INCLUDE			= -I includes


##############################  COLORS  ###################################

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[3;92m
YELLOW = \033[0;93m
BLUE = \033[3;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


##############################  SOURCES  #####################################

OBJ_DIR			= object

SRC_FILES		= minishell.c \
				  utils/utils.c \
				  utils/utils2.c \
				  utils/ft_split.c \
				  utils/isascii.c \
				  utils/free_all.c \
				  utils/ft_strjoin.c \
				  utils/len.c \
				  parsing/env/pars_env.c \
				  parsing/env/free_env.c \
				  parsing/env/find_env_name.c \
				  parsing/env/env_to_tab.c\
				  parsing/lexer/tokenizer.c \
				  parsing/lexer/dup_token.c \
				  parsing/lexer/token_identifier.c \
				  parsing/lexer/free_token.c \
				  builtins/pwd.c \
				  builtins/cd.c \
				  builtins/export.c \
				  signals/signal_handler.c \
				  errors/puterrors.c \
				  execution/execute.c \
				  execution/free_cmds.c \
				  execution/check_cmds.c \
				  execution/make_lstcmd.c \
				  execution/wait_and_close.c \
				  execution/here_doc/here_doc.c \
				  execution/here_doc/here_doc_env.c \
				  execution/here_doc/create_tmp_file.c

OBJ             = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

##############################  RULES  #######################################

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) $(OBJ) $(CFLAGS) $(READLINE_FLAG) $(INCLUDE) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(dir $(OBJ))

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${GRAY}Minishell object files cleaned! ${DEF_COLOR}"

fclean: clean
	@rm -f $(NAME)
	@echo "${YELLOW}Minishell executable files cleaned! ${DEF_COLOR}"

re: fclean all

.PHONY: all clean fclean re
