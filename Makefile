# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-win <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 17:42:57 by gde-win           #+#    #+#              #
#    Updated: 2024/04/11 17:29:34 by gde-win          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			philo
CC :=			cc
CFLAGS :=		-Wall -Wextra -Werror
ASAN_FLAGS :=	-fsanitize=address -g
INC_FILES :=	-I/inc
FUNCTIONS :=	philo.c
LIBFT :=		libft
LLIBFT :=		$(addsuffix /libft.a, $(LIBFT))
SRCS_DIR :=		src
SRCS :=			$(addprefix $(SRCS_DIR)/, $(FUNCTIONS))
OBJS_DIR :=     obj
OBJS :=         $(addprefix $(OBJS_DIR)/, $(SRCS:$(SRCS_DIR)/%.c=%.o))
GREEN :=        \033[0;32m
RED :=          \033[0;31m
END_COLOR :=    \033[0m
MAKE :=			make

all: $(LIBFT)
	@echo "$(GREEN)Making philo"
	@mkdir -p $(OBJS_DIR)
	@echo -n \[
	@make $(NAME)
	@echo "]$(END_COLOR)"

$(LIBFT):
		@$(MAKE) -C $@

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $^ -Wl,$(LLIBFT) -pthread -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FILES)
		@echo -n =

asan: CFLAGS += $(ASAN_FLAGS)
asan: MAKE += asan
asan: all
	@echo "$(RED)ADDRESS SANITIZER ON$(END_COLOR)"

clean:
ifeq ($(wildcard $(OBJS_DIR)),)
else
		@echo "$(RED)Removing philo objects$(END_COLOR)"
		@rm -rf $(OBJS_DIR)
endif
		@make clean -C $(LIBFT)

fclean: clean
ifeq ($(wildcard $(NAME)),)
else
		@echo "$(RED)Removing philo executable$(END_COLOR)"
		@rm -rf $(NAME)
endif
		@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all asan clean fclean re libft lexer parser
