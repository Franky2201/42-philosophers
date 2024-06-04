# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-win <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 17:42:57 by gde-win           #+#    #+#              #
#    Updated: 2024/06/04 19:36:26 by gde-win          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			philo
CC :=			cc
CFLAGS :=		-Wall -Wextra -Werror -O3
ASAN_FLAGS :=	-fsanitize=address -g
TSAN_FLAGS :=	-fsanitize=thread -g
INC_FILES :=	-I/inc
FUNCTIONS :=	atoi.c \
				check_args.c \
				init.c \
				itoa.c \
				live.c \
				live_utils.c \
				philo.c \
				safe_mutexes.c \
				safe_threads.c \
				strcmp.c \
				philo_utils.c
SRCS_DIR :=		src
SRCS :=			$(addprefix $(SRCS_DIR)/, $(FUNCTIONS))
OBJS_DIR :=		obj
OBJS :=			$(addprefix $(OBJS_DIR)/, $(SRCS:$(SRCS_DIR)/%.c=%.o))
GREEN :=		\033[0;32m
RED :=			\033[0;31m
NO_COLOR :=		\033[0m
MAKE :=			make

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
		@mkdir -p $@
		@echo "$(GREEN)Making philo"
		@echo -n \[

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $^ -pthread -o $@
		@echo "]$(NO_COLOR)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FILES)
		@echo -n =

asan: CFLAGS += $(ASAN_FLAGS)
asan: MAKE += asan
asan: all
		@echo "$(RED)ADDRESS SANITIZER ON$(END_COLOR)"

tsan: CFLAGS += $(TSAN_FLAGS)
tsan: all
		@echo "$(RED)THREAD SANITIZER ON$(END_COLOR)"

clean:
ifeq ($(wildcard $(OBJS_DIR)),)
else
		@echo "$(RED)Removing philo objects$(END_COLOR)"
		@rm -rf $(OBJS_DIR)
endif

fclean: clean
ifeq ($(wildcard $(NAME)),)
else
		@echo "$(RED)Removing philo executable$(END_COLOR)"
		@rm -rf $(NAME)
endif

re: fclean all

.PHONY: all asan clean fclean re libft lexer parser
