# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 16:02:37 by avan-pra          #+#    #+#              #
#    Updated: 2020/08/05 12:46:22 by velovo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= megashell

CFLAGS			= -Wall -Wextra -Werror #-g3 #-fsanitize=address

SRC				=	./srcs/reader/inter_line.c\
					./srcs/reader/read_utils.c\
					./srcs/reader/special_event1.c\
					./srcs/reader/special_event2.c\
					./srcs/reader/special_event3.c\
					./srcs/reader/multiline.c\
					./srcs/reader/interactive_read.c\
					./srcs/spliter/check_pipe.c\
					./srcs/spliter/check_quote.c\
					./srcs/spliter/split_r_in_out1_part1.c\
					./srcs/spliter/split_r_in_out1_part2.c\
					./srcs/spliter/split_r_in_out2.c\
					./srcs/spliter/split_pipe.c\
					./srcs/spliter/split_pipe_utils.c\
					./srcs/spliter/split_semi_colon.c\
					./srcs/builtin/builtin.c\
					./srcs/builtin/builtin2.c\
					./srcs/environement/handle_env.c\
					./srcs/environement/env_utils.c\
					./srcs/environement/new_env.c\
					./srcs/environement/del_env.c\
					./srcs/better_split/doll.c\
					./srcs/better_split/doll_utils.c\
					./srcs/better_split/enhanced_split.c\
					./srcs/better_split/advance.c\
					./srcs/better_split/count_split.c\
					./srcs/better_split/count_words.c\
					./srcs/better_split/fill_word.c\
					./srcs/better_split/fill_word_utils.c\
					./srcs/executor/exec_prog.c\
					./srcs/executor/exec_prog_utils.c\
					./srcs/executor/file_problem.c\
					./srcs/executor/setup_exec.c\
					./srcs/executor/true_exec_prog.c\
					./srcs/executor/preliminar1.c\
					./srcs/executor/preliminar2.c\
					./srcs/main/close_all.c\
					./srcs/main/main.c\
					./srcs/main/sign_handle.c\
					./srcs/main/prompt.c\
					./srcs/main/main_utils1.c\
					./srcs/main/main_utils2.c\

ROAD_S			= $(SRC)

ROAD_O			= $(OBJ)

ROAD_B			= $(SRCB)


OBJ				= $(SRC:.c=.o)

CC				= clang

HEADER_DIR		= -I./head/get_next_line.h -I./head/megashell.h 

$(NAME) :		$(OBJ)
				cd libft && make
				$(CC) $(OBJ) libft/libft.a -ltermcap -o $(NAME)

LIBFT			= libft

all :			$(NAME)

clean :
				cd libft && make clean
				rm -f $(ROAD_O)

fclean :
				cd libft && make fclean
				rm -f $(ROAD_O)
				rm -f $(NAME)

re : 			fclean all

.PHONY: 		all clean fclean re
