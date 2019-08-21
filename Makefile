# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malannys <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 15:59:28 by malannys          #+#    #+#              #
#    Updated: 2019/08/21 21:16:27 by malannys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project executable
NAME := ft_ls

# Paths
SRCDIR := ./src/
OBJDIR := ./obj/
INCDIR := ./inc/

# Srcs, objs
SRCNAMES := main.c ft_ls.c sorting.c list.c print.c error_handling.c
SRC := $(addprefix $(SRCDIR), $(SRCNAMES))
OBJ := $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

# Libft
LIBDIR := ./libft/
LIBINCDIR := $(LIBDIR)/inc/
LIB := $(LIBDIR)/libft.a

# Compilation commands and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror $(DEBUG)
DEBUG := -g

.PHONY: all fclean clean

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)
	$(CC) -c $(CFLAGS) -I$(INCDIR) -I$(LIBINCDIR) $< -o $@

$(LIB):
	make -C $(LIBDIR)

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBDIR) fclean

re: fclean all
