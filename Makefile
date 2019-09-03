# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malannys <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 15:59:28 by malannys          #+#    #+#              #
#    Updated: 2019/09/03 20:51:47 by abartole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project executable
NAME := ft_ls

# Paths
SRCDIR := ./src/
OBJDIR := ./obj/
INCDIR := ./inc/

# Srcs, objs
SRCNAMES := ft_ls.c sorting.c list.c print.c error_handling.c options_parser.c check_options.c
SRC := $(addprefix $(SRCDIR), $(SRCNAMES))
OBJ := $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

# Libft
LIBDIR := ./libft/
LIBINCDIR := $(LIBDIR)/inc/
LIB := $(LIBDIR)/libft.a

# Compilation commands and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror

.PHONY: all fclean clean debug

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJ): $(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBINCDIR) -c $< -o $@

$(LIB):
	@make -C $(LIBDIR)

debug1:
	$(CC) -g $(CFLAGS) $(SRC) libft/ft_strlen.c libft/ft_strcmp.c libft/ft_strcpy.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_putchar_fd.c libft/ft_putendl.c libft/ft_putstr.c libft/ft_putstr_fd.c libft/ft_strcat.c libft/ft_strnew.c libft/ft_memset.c libft/ft_putendl_fd.c -I$(INCDIR) -I$(LIBINCDIR) -o $(NAME)

debug:
	$(CC) -g $(CFLAGS) $(SRC) -I$(INCDIR) -I$(LIBINCDIR) $(LIB) -o $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
