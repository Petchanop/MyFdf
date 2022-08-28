# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiya-is <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 17:31:19 by npiya-is          #+#    #+#              #
#    Updated: 2022/08/27 14:56:56 by npiya-is         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= fdf.c\
	fdf_utils.c\
		include/getnextline/get_next_line.c\
		include/getnextline/get_next_line_utils.c\

SRCS2= testfdf.c\
		fdf_utils.c\
		ft_format_input.c\
		ft_create_data.c\
		include/getnextline/get_next_line.c\
		include/getnextline/get_next_line_utils.c\

SRCS3= testfdf.c\
		fdf_write_line.c\
		ft_format_input.c\
		ft_create_data.c\
		include/Mae/get_next_line.c\
		include/Mae/get_next_line_utils.c\

OBJS=$(SRCS:%.c=%.o)

OBJS2=$(SRCS2:%.c=%.o)

CC= gcc -g -Wall -Wextra -Werror

NAME= fdfpet

NAME2= testfdf

NAME3= testfdf2

# %.o: %.c
# 	$(CC) -Imlx -c $< -o $@

all:$(NAME)

test:$(NAME2)

test2:$(NAME3)

$(NAME): $(OBJS)
	make -C include/ft_printf/
	$(CC) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(NAME2):
	make -C include/ft_printf/
	$(CC) -o $(NAME2) $(SRCS2) -Lmlx -lmlx -framework OpenGL -framework AppKit -L./include/ft_printf -lftprintf


$(NAME3):
	make -C include/ft_printf/
	$(CC) -o $(NAME3) $(SRCS3) -Lmlx -lmlx -framework OpenGL -framework AppKit -L./include/ft_printf -lftprintf

fclean:
	rm -rf $(NAME)

fclean2:
	rm -rf $(NAME2)

fclean3:
	rm -rf $(NAME3)

re: fclean all

re2: fclean2 test 

re3: fclean3 test2 

#gcc -g -Wall -Wextra -Werror -o testfdf testfdf.c fdf_utils.c include/getnextline/get_next_line.c include/getnextline/get_next_line_utils.c -Lmlx -lmlx -framework OpenGL -framework AppKit -L./include/ft_printf -lftprintf