# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 16:07:03 by nfour             #+#    #+#              #
#    Updated: 2024/07/08 11:15:00 by nfour            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include rsc/mk/source.mk
include rsc/mk/color.mk


CREATE_LIB	= ar rcs
NAME		= libft.a
# CC			= gcc
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g3
# CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@printf "$(MAGENTA)"
	${CREATE_LIB} -o $(NAME) $(OBJ)
	@printf "$(RESET)$(GREEN)$(NAME) created$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p ${ALL_OBJ_DIR} 

$(OBJ_DIR)/%.o: $(SRC)%.c
	@printf "$(YELLOW)$<$(RESET) $(BRIGHT_BLACK)-->$(RESET) $(BRIGHT_BLUE)$@$(RESET)\n"
	@$(CC) -o $@ -c $< $(CFLAGS)

clean :
ifeq ($(shell [ -d ${OBJ_DIR} ] && echo 0 || echo 1), 0)
	@${RM} $(OBJ_DIR)
	@printf "$(RED)$(OBJ_DIR) deleted$(RESET)\n"
endif

fclean : clean
	@${RM} $(NAME)
	@${RM} ${OBJ_DIR}
	@ make -s -C list fclean
	@printf "$(RED)$(NAME) deleted$(RESET)\n"

re : fclean all

.PHONY: clean fclean all re

