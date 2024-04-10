# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-win <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 13:05:02 by gde-win           #+#    #+#              #
#    Updated: 2024/04/10 22:21:52 by gde-win          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			libft.a
CC :=			cc
AR :=			ar
CFLAGS :=		-Wall -Wextra -Werror
ASAN_FLAGS:=	-fsanitize=address -g
INC_FILES :=	-I/inc
FUNCTIONS :=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_llitoa.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstfirst.c \
				ft_lstinsert.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_printf.c \
				ft_printf_putchar.c \
				ft_printf_putnbr.c \
				ft_printf_putstr.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				get_next_line.c \
				get_next_line_utils.c
SRCS_DIR :=		src
SRCS :=			$(addprefix $(SRCS_DIR)/, $(FUNCTIONS))
OBJS_DIR :=		obj
OBJS :=			$(addprefix $(OBJS_DIR)/, $(SRCS:$(SRCS_DIR)/%.c=%.o))
GREEN :=		\033[0;32m
RED :=			\033[0;31m
END_COLOR :=	\033[0m

all:
	@echo "$(GREEN)Making libft"
	@mkdir -p $(OBJS_DIR)
	@echo -n \[
	@make $(NAME)
	@echo "]$(END_COLOR)"

$(NAME): $(OBJS)
	@$(AR) -rc $@ $^

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FILES)
	@echo -n =

asan: CFLAGS += $(ASAN_FLAGS)
asan: all
	@echo "$(RED)ADDRESS SANITIZER ON$(END_COLOR)"

clean:
ifeq ($(wildcard $(OBJS_DIR)),)
else
	@echo "$(RED)Removing libft objects$(END_COLOR)"
	@rm -rf $(OBJS_DIR)
endif

fclean: clean
ifeq ($(wildcard $(NAME)),)
else
	@echo "$(RED)Removing libft archive$(END_COLOR)"
	@rm -rf $(NAME)
endif

re: fclean all

.PHONY: all asan clean fclean re
