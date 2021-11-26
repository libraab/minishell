# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 10:50:15 by abouhlel          #+#    #+#              #
#    Updated: 2021/11/26 14:08:17 by abouhlel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell

#################### * F I L E S * #############################################
FOLDER_HEADER		= includes/
FOLDER				= srcs/

HEADER_FILE 		= minishell.h

SRCS				= minishell.c \
						lexer.c \
						ft_error.c \
						ft_split_pipe.c \
						ft_split_pipe_utils.c \
						ft_memory.c \
						ft_utils.c \
						ft_tokenize.c \
						ft_collect.c \
						ft_replace_dollar.c \

SRC					= $(addprefix ${FOLDER},${SRCS})
HEADERS				= $(addprefix ${FOLDER_HEADER},${HEADER_FILE})

OBJS				= ${SRC:.c=.o}

################################################################################

#################### * C O M P I L A T I O N * #################################
CC					= gcc
CFLAGS  			= -Wall -Wextra -Werror -g -fsanitize=address
RM					= rm -rf
MAKE_EXT			= @make -s --no-print-directory -C
LIBR				= libreadline.a
OBJ					= ${OBJS}

UNAME_S				= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS 			= -L ./libft -lft -lreadline
endif
ifeq ($(UNAME_S),Darwin)
	LIBS 			= -L ./libft -lft -lreadline
endif

COMPIL	= $(CC) $(CFLAGS) ${OBJ} ${LIBR} -lncurses $(LIBS) -o $(NAME)

################################################################################

######################### * R U L E S * ########################################

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
			@printf "Object files have been deleted 🚮\n"
			@printf $(reset)

fclean:		clean
			$(MAKE_EXT) ./libft fclean
			@${RM} $(NAME)
			@printf $(magenta)
			@printf "Your folder is now clean 🧹\n"
			@printf $(reset)

.PHONY: 	all clean fclean re

#################################################################################

#################### * C O L O R *** S E T T I N G * ############################

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
