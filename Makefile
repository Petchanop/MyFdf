# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 17:31:19 by npiya-is          #+#    #+#              #
#    Updated: 2022/10/18 20:15:08 by npiya-is         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR= srcs/

SRCS= $(SRCS_DIR)fdf.c\
	$(SRCS_DIR)fdf_keymap.c\
	$(SRCS_DIR)fdf_adjust_point.c\
	$(SRCS_DIR)fdf_finddxdy.c \
	$(SRCS_DIR)fdf_write_line.c\
	$(SRCS_DIR)fdf_rotate_point.c \
	$(SRCS_DIR)fdf_checkpoint.c \
	$(SRCS_DIR)ft_format_input.c \
	$(SRCS_DIR)ft_create_data.c \
	$(SRCS_DIR)fdf_assign_color.c \

SRCS_INCLUDE= include/getnextline/get_next_line.c\
	include/getnextline/get_next_line_utils.c\

BUILD_DIR = build

OBJS=$(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS_INC=$(SRC_INCLUDE:%.c=$(BUILD_DIR)/%.o)

CC= gcc  -g -Wall -Wextra -Werror

NAME= fdfpet

all:$(NAME)

$(NAME):
	@make -C include/ft_printf/
	@make -C mlx/
	$(CC) -o $(NAME) $(SRCS) $(SRCS_INCLUDE) -Lmlx -lmlx -framework OpenGL -framework AppKit -L./include/ft_printf -lftprintf

clean:
	rm -rf mlx/*.o
	rm -rf include/getnextline/*.o
	make -C include/ft_printf clean
	rm -rf *.o

fclean:clean
	rm -rf $(NAME)

re: fclean all