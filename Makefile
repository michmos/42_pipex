# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 13:49:18 by mmoser            #+#    #+#              #
#    Updated: 2024/03/06 09:14:08 by mmoser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex

LIBS		:= ft
LIBS_TARGET	:= external_libs/libft.a

SRC_DIR		:= src

SRCS		:= main.c helper_foos1.c free_heap.c cmd_pipeline.c set_cmd_path.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LINKERFLAGS	:= $(addprefix -L ,$(dir $(LIBS_TARGET))) $(addprefix -l, $(LIBS))
RM			:= rm -rf
CFLAGS		:= -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(OBJS) $(LINKERFLAGS) -o $@
	@printf "$(CREATED)" $(NAME) $(CUR_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

%.a:
	$(MAKE) -C $(@D) all

clean:
	$(MAKE) -C $(dir $(LIBS_TARGET)) clean
	$(RM) $(BUILD_DIR)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)

fclean:
	$(MAKE) -C $(dir $(LIBS_TARGET)) fclean
	$(RM) $(BUILD_DIR)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)
	$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME)  $(CUR_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

print-%:
	$(info $($*))

.PHONY: clean fclean re

# ----------------------------------- colors --------------------------------- #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# ----------------------------------- messages ------------------------------- #

CUR_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED	:= $(MAGENTA) $(BOLD) REMOVED %s (%s) $(RESET)\n\n
CREATED	:= $(GREEN) $(BOLD) CREATED %s (%s) $(RESET)\n\n
UPDATED	:= $(GREEN) $(BOLD) CREATED OR UPDATED %s (%s) $(RESET)\n\n
