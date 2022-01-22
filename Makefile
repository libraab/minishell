# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 10:50:15 by abouhlel          #+#    #+#              #
#    Updated: 2022/01/22 10:50:48 by abouhlel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell

# ███████╗    ██╗    ██╗         ███████╗    ███████╗
# ██╔════╝    ██║    ██║         ██╔════╝    ██╔════╝
# █████╗      ██║    ██║         █████╗      ███████╗
# ██╔══╝      ██║    ██║         ██╔══╝      ╚════██║
# ██║         ██║    ███████╗    ███████╗    ███████║
# ╚═╝         ╚═╝    ╚══════╝    ╚══════╝    ╚══════╝

FOLDER_HEADER		= includes/
FOLDER				= srcs/

HEADER_FILE 		= minishell.h

SRCS				=	ft_dollar1.c \
						ft_dollar2.c \
						ft_dollar3.c \
						ft_collect.c \
						ft_error.c \
						ft_memory.c \
						ft_split_pipe_utils.c \
						ft_split_pipe.c \
						ft_tokenize.c \
						ft_utils.c \
						ft_signal.c \
						lexer.c \
						minishell.c \
						ft_print.c \
						exec/middle_cmds.c \
						exec/multipipex.c \
						exec/multi_utils_and_redir.c \
						exec/pipex_utils.c \
						exec/get_path.c \
						exec/take_env.c \
						exec/find_cmd.c \
						exec/tab_len.c \
						exec/free_tab.c \
						exec/ft_cd.c \
						exec/ft_signal_exec.c \
						exec/chk_exec_built.c \
						exec/ft_pwd.c \
						exec/ft_env.c \
						exec/ft_unset.c \
						exec/ft_unset_utils.c \
						exec/ft_echo.c \
						exec/ft_export.c \
						exec/take_redirs.c \
						exec/make_redirs.c \
						exec/ft_export_utils.c \
						exec/copy_env.c \
						exec/ft_exit.c

SRC					= $(addprefix ${FOLDER},${SRCS})
HEADERS				= $(addprefix ${FOLDER_HEADER},${HEADER_FILE})

OBJS				= ${SRC:.c=.o}

#  ██████╗     ██████╗     ███╗   ███╗    ██████╗     ██╗    ██╗
# ██╔════╝    ██╔═══██╗    ████╗ ████║    ██╔══██╗    ██║    ██║
# ██║         ██║   ██║    ██╔████╔██║    ██████╔╝    ██║    ██║
# ██║         ██║   ██║    ██║╚██╔╝██║    ██╔═══╝     ██║    ██║
# ╚██████╗    ╚██████╔╝    ██║ ╚═╝ ██║    ██║         ██║    ███████╗
#  ╚═════╝     ╚═════╝     ╚═╝     ╚═╝    ╚═╝         ╚═╝    ╚══════╝

CC					= gcc
CFLAGS  			= -Wall -Wextra -Werror #-g -fsanitize=address
RM					= rm -rf
MAKE_EXT			= @make -s --no-print-directory -C
LIBR				= -lreadline -L /Users/$(USER)/.brew/Cellar/readline/8.1.1/lib
OBJ					= ${OBJS}

UNAME_S				= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS 			= -L ./libft -lft -lreadline
endif
ifeq ($(UNAME_S),Darwin)
	LIBS 			= -L ./libft -lft -lreadline
endif

COMPIL	= $(CC) $(CFLAGS) ${OBJ} ${LIBR} -lncurses $(LIBS) -o $(NAME) 

# ██████╗     ██╗   ██╗    ██╗         ███████╗    ███████╗
# ██╔══██╗    ██║   ██║    ██║         ██╔════╝    ██╔════╝
# ██████╔╝    ██║   ██║    ██║         █████╗      ███████╗
# ██╔══██╗    ██║   ██║    ██║         ██╔══╝      ╚════██║
# ██║  ██║    ╚██████╔╝    ███████╗    ███████╗    ███████║
# ╚═╝  ╚═╝     ╚═════╝     ╚══════╝    ╚══════╝    ╚══════╝

$(NAME):	${OBJ}
			@printf $(blue)
			@printf "\n"
			@printf $(magenta)
			$(MAKE_EXT) ./libft
			@$(COMPIL)
			@printf $(green)
			@printf "💚 YOUR MINISHELL IS READY 💚 \n"
			@printf $(reset)

all:		${NAME}

%.o: %.c	$(HEADERS)
			@printf $(yellow)
			@printf " Generating minishell objects... %-33.33s\r" $@
			@$(CC) -c $(CFLAGS) -o $@ $<
			@printf $(reset)

re: 		fclean all

clean:
			$(MAKE_EXT) ./libft clean
			@${RM} ${OBJ}
			@printf $(magenta)
			@printf "Object files have been deleted ✅\n"
			@printf $(reset)

fclean:		clean
			$(MAKE_EXT) ./libft fclean
			@${RM} $(NAME)
			@printf $(cyan)
			@printf "✨ Your folder is now clean ✨\n"
			@printf $(reset)

.PHONY: 	all clean fclean re


#  ██████╗     ██████╗     ██╗          ██████╗     ██████╗
# ██╔════╝    ██╔═══██╗    ██║         ██╔═══██╗    ██╔══██╗
# ██║         ██║   ██║    ██║         ██║   ██║    ██████╔╝
# ██║         ██║   ██║    ██║         ██║   ██║    ██╔══██╗
# ╚██████╗    ╚██████╔╝    ███████╗    ╚██████╔╝    ██║  ██║
#  ╚═════╝     ╚═════╝     ╚══════╝     ╚═════╝     ╚═╝  ╚═╝


black 				=	"[1;30m"
red 				=	"[1;31m"
green 				=	"[1;32m"
yellow 				=	"[1;33m"
blue 				=	"[1;34m"
magenta 			=	"[1;35m"
cyan 				=	"[1;36m"
white 				=	"[1;37m"

bg_black 			=	"[40m"
bg_red 				=	"[41m"
bg_green 			=	"[42m"
bg_yellow 			=	"[43m"
bg_blue 			=	"[44m"
bg_magenta 			=	"[45m"
bg_cyan 			=	"[46m"
bg_white 			=	"[47m"

reset 				=	"[0m"


# ███╗   ███╗    ██╗    ███╗   ██╗    ██╗    ███████╗    ██╗  ██╗    ███████╗    ██╗         ██╗
# ████╗ ████║    ██║    ████╗  ██║    ██║    ██╔════╝    ██║  ██║    ██╔════╝    ██║         ██║
# ██╔████╔██║    ██║    ██╔██╗ ██║    ██║    ███████╗    ███████║    █████╗      ██║         ██║
# ██║╚██╔╝██║    ██║    ██║╚██╗██║    ██║    ╚════██║    ██╔══██║    ██╔══╝      ██║         ██║
# ██║ ╚═╝ ██║    ██║    ██║ ╚████║    ██║    ███████║    ██║  ██║    ███████╗    ███████╗    ███████╗
# ╚═╝     ╚═╝    ╚═╝    ╚═╝  ╚═══╝    ╚═╝    ╚══════╝    ╚═╝  ╚═╝    ╚══════╝    ╚══════╝    ╚══════╝

# 									██████╗ ██╗   ██╗
# 									██╔══██╗╚██╗ ██╔╝
# 									██████╔╝ ╚████╔╝
# 									██╔══██╗  ╚██╔╝
# 									██████╔╝   ██║
# 									╚═════╝    ╚═╝

#  █████╗     ██████╗      ██████╗     ██╗   ██╗    ██╗  ██╗    ██╗         ███████╗    ██╗
# ██╔══██╗    ██╔══██╗    ██╔═══██╗    ██║   ██║    ██║  ██║    ██║         ██╔════╝    ██║
# ███████║    ██████╔╝    ██║   ██║    ██║   ██║    ███████║    ██║         █████╗      ██║
# ██╔══██║    ██╔══██╗    ██║   ██║    ██║   ██║    ██╔══██║    ██║         ██╔══╝      ██║
# ██║  ██║    ██████╔╝    ╚██████╔╝    ╚██████╔╝    ██║  ██║    ███████╗    ███████╗    ███████╗
# ╚═╝  ╚═╝    ╚═════╝      ╚═════╝      ╚═════╝     ╚═╝  ╚═╝    ╚══════╝    ╚══════╝    ╚══════╝

# 								 █████╗ ███╗   ██╗██████╗
# 								██╔══██╗████╗  ██║██╔══██╗
# 								███████║██╔██╗ ██║██║  ██║
# 								██╔══██║██║╚██╗██║██║  ██║
# 								██║  ██║██║ ╚████║██████╔╝
# 								╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝

# ██╗  ██╗    ██████╗      ██████╗     ██╗   ██╗    ██╗  ██╗    ██╗  ██╗     ██████╗     ██████╗
# ██║  ██║    ██╔══██╗    ██╔═══██╗    ██║   ██║    ██║ ██╔╝    ██║  ██║    ██╔═══██╗    ██╔══██╗
# ███████║    ██████╔╝    ██║   ██║    ██║   ██║    █████╔╝     ███████║    ██║   ██║    ██████╔╝
# ██╔══██║    ██╔══██╗    ██║   ██║    ██║   ██║    ██╔═██╗     ██╔══██║    ██║   ██║    ██╔══██╗
# ██║  ██║    ██████╔╝    ╚██████╔╝    ╚██████╔╝    ██║  ██╗    ██║  ██║    ╚██████╔╝    ██║  ██║
# ╚═╝  ╚═╝    ╚═════╝      ╚═════╝      ╚═════╝     ╚═╝  ╚═╝    ╚═╝  ╚═╝     ╚═════╝     ╚═╝  ╚═╝
