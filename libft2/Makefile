# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/14 10:42:27 by abouhlel          #+#    #+#              #
#    Updated: 2021/10/14 10:48:20 by abouhlel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
AR=ar
ARFLAGS=rc
CFLAGS=-Wall -Wextra -Werror 
NAME=libft.a
SRC=ft_strlen.c ft_atoi.c ft_memset.c ft_memcmp.c\
	ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	ft_strlcpy.c ft_split.c ft_calloc.c ft_strncpy.c \
	ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	ft_memchr.c ft_strdup.c ft_strncmp.c ft_strnstr.c \
	ft_calloc.c ft_strrchr.c ft_toupper.c ft_tolower.c \
	ft_strmapi.c ft_substr.c ft_strjoin.c ft_isalpha.c \
	ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_itoa.c \
	ft_putendl_fd.c ft_putnbr_fd.c \

BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstmap.c ft_lstsize.c ft_lstlast.c ft_lstiter.c\
	
OBJ=$(SRC:.c=.o)

OBJ_B=$(BONUS:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	ranlib $(NAME)

bonus:	${OBJS} ${OBJ_B}
		ar rcs ${NAME} ${OBJS} ${OBJ_B}

all: $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME)

re: fclean all
#################################################################################
#                                                                               #
#                   ##                                             #####        #
#                   ##                                             #            #
#                   ##                                           #######        #
#                   ##                                              ##          #
#       #####       ##          ####           #    #    #          ##          #
#       #           ##         #    #          #    #    #          ##          #
#     ########      ########################### #### ####           ##          #
#                                                                               #
#################################################################################
