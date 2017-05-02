# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssmith <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 08:55:56 by ssmith            #+#    #+#              #
#    Updated: 2017/04/27 14:11:36 by ssmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

CC=cc

C_FLAGS=-Wall -Wextra -Werror

SRC_DIR=./

OBJ_DIR=./build/

INC_DIR=./includes/

# Memory functions.
C_FILES =	ft_bzero.c \
			ft_memset.c \
			ft_memchr.c \
			ft_memcpy.c \
			ft_memcmp.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memalloc.c \
			ft_memdel.c \

# I/O functions.
C_FILES +=	ft_putchar.c \
			ft_putchar_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \

# String functions.
C_FILES +=	ft_strlen.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strdup.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strclr.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_itoa.c \
			ft_atoi.c \

# List functions.
C_FILES +=	ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \

# Personal functions.
C_FILES += ft_strisdigit.c \
		   ft_strisalnum.c \
		   ft_strisprint.c \
		   ft_strisalpha.c \
		   ft_maxword.c \
		   ft_lastchr.c \
		   ft_itoal.c \
		   ft_findchr.c \
		   ft_delendchr.c \
		   ft_itoa_basel.c \
		   ft_itoa_base.c \
		   ft_strwhite.c \
		   ft_chrcat.c \
		   ft_itoau.c \
		   ft_strwcat.c \
		   ft_findnchr.c \
		   pf_adjust.c \
		   pf_chr.c \
		   pf_find.c \
		   pf_nbr.c \
		   pf_run.c \
		   ft_dbrealloc.c \
		   ft_dbrealloc_chr.c \
		   ft_intrealloc.c \
		   ft_chrrealloc.c \
		   ft_strrcat.c \
		   ft_printf.c \
		   ft_strupper.c \
		   ft_strlower.c \
		   ft_realloc_int.c \
		   ft_strcstr.c \
           ft_realloc.c \

# get_next_line
C_FILES += get_next_line.c \

SOURCES=$(addprefix $(C_FILES))

INCLUDES=$(addprefix -I, $(INC_DIR))

OBJECTS=$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(C_FILES)))

default : all

test : $(NAME)
		$(MAKE) -C ./test/ re
		./test/test.out

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJECTS)
		@echo "Archiving object files..."
		@ar rc $(NAME) $(OBJECTS)
		@echo "Done."
		@echo "Indexing..."
		@ranlib $(NAME)
		@echo "Done."

$(OBJ_DIR) :
		@echo "Creating build directory..."
		@mkdir -p $(OBJ_DIR)
		@echo "Done."

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
				$(CC) $(C_FLAGS) -c $< -o $@ $(INCLUDES)

fclean : clean
		@echo "Removing $(NAME)..."
		@rm -rf $(NAME)
		@echo "Done."

clean :
		@echo "Cleaning last build..."
		@rm -rf $(OBJ_DIR)
		@echo "Done."

re : fclean all

.PHONY : clean fclean re test
