#!/bin/bash

# check if the current directory is a git repository
if [ ! -d ".git" ]; then
	echo "This is not a git repository"
	exit 1
fi

# check if the current directory is an empty git repository
if [ ! -z "$(ls .)" ]; then
	echo "This is not an empty git repository"
	exit 1
fi

# check for repo name provided
if [ -z "$1" ]; then
	echo "Repo name is required"
	exit 1
fi

REPO_NAME="$1"
# LIBFT_MODULE="git@github.com:Ycaro02/sub_libft.git"

# init the git submodule for libft
# git submodule init
# git submodule add ${LIBFT_MODULE} libft
# git submodule update

echo "Initializing the repository with name: ${REPO_NAME}, Clone libft and remove the .git dir"
git clone git@github.com:Ycaro02/sub_libft.git libft
rm -rf libft/.git

echo "Creating the Makefile and the source files dir"
# Create Makefile
cat <<EOF > Makefile
include libft/rsc/mk/color.mk
include rsc/mk/source.mk

NAME            =   ${REPO_NAME}
CC              =   clang

all:        \$(NAME)

\$(NAME): \$(LIBFT) \$(LIST) \$(OBJ_DIR) \$(OBJS)
	@\$(MAKE_LIBFT)
	@\$(MAKE_LIST)
	@printf "\$(CYAN)Compiling \${NAME} ...\$(RESET)\n"
	@\$(CC) \$(CFLAGS) -o \$(NAME) \$(OBJS) \$(LIBFT) \$(LIST) -lm
	@printf "\$(GREEN)Compiling \$(NAME) done\$(RESET)\n"

\$(LIST):
ifeq (\$(shell [ -f \${LIST} ] && echo 0 || echo 1), 1)
	@printf "\$(CYAN)Compiling list...\$(RESET)\n"
	@\$(MAKE_LIST)
	@printf "\$(GREEN)Compiling list done\$(RESET)\n"
endif

\$(LIBFT):
ifeq (\$(shell [ -f \${LIBFT} ] && echo 0 || echo 1), 1)
	@printf "\$(CYAN)Compiling libft...\$(RESET)\n"
	@\$(MAKE_LIBFT)
	@printf "\$(GREEN)Compiling libft done\$(RESET)\n"
endif

\$(OBJ_DIR):
	@mkdir -p \$(ALL_SRC_DIR)

\$(OBJ_DIR)/%.o: \$(SRC_DIR)/%.c
	@printf "\$(YELLOW)Compile \$<\$(RESET) \$(BRIGHT_BLACK)-->\$(RESET) \$(BRIGHT_MAGENTA)\$@\$(RESET)\n"
	@\$(CC) \$(CFLAGS) -o \$@ -c \$<
bonus: clear_mandatory \$(NAME)

clear_mandatory:
ifeq (\$(shell [ -f \${OBJ_DIR}/main.o ] && echo 0 || echo 1), 0)
	@printf "\$(RED)Clean mandatory obj \$(RESET)\n"
	@rm -rf \${OBJ_DIR}
endif

clean:
ifeq (\$(shell [ -d \${OBJ_DIR} ] && echo 0 || echo 1), 0)
	@\$(RM) \$(OBJ_DIR)
	@printf "\$(RED)Clean \$(OBJ_DIR) done\$(RESET)\n"
	@\$(RM)
endif

fclean:		clean_lib clean
	@\$(RM) \$(NAME)
	@printf "\$(RED)Clean \$(NAME)\$(RESET)\n"

clean_lib:
	@\$(MAKE_LIST) fclean
	@\$(MAKE_LIBFT) fclean
	@printf "\$(RED)Clean libft, list\$(RESET)\n"

test: \$(NAME)
	@./\$(NAME)

# @ulimit -c unlimited
leak thread debug: clean \$(NAME)
	@printf	"\$(CYAN)CFLAGS: \$(CFLAGS)\$(RESET)\n"
# @./\$(NAME)

re: clean \$(NAME)

.PHONY:		all clean fclean re bonus" > Makefile
EOF

# Create the necessary directories
mkdir -p rsc src include
cp -r libft/rsc/mk rsc
cp -r libft/rsc/sh rsc


echo "Creating the source.mk file"
# initialize the source.mk file
cat <<EOF > rsc/mk/source.mk
CFLAGS			=	-Wall -Wextra -Werror -O3

OBJ_DIR			=	obj

ALL_SRC_DIR 	=	obj

SRC_DIR 		=	src

MAIN_MANDATORY 	=	main.c

SRCS			=	test.c

# SRCS_BONUS		=	main_bonus.c

MAKE_LIBFT		=	make -s -C libft -j

MAKE_LIST		=	make -s -C libft/list -j

LIBFT			= 	libft/libft.a

LIST			= 	libft/list/linked_list.a

OBJS 			= \$(addprefix \$(OBJ_DIR)/, \$(SRCS:.c=.o))

RM			=	rm -rf

ifeq (\$(findstring bonus, \$(MAKECMDGOALS)), bonus)
ASCII_NAME	= "bonus"
SRCS += \$(SRCS_BONUS)
else
SRCS += \$(MAIN_MANDATORY)
endif

ifeq (\$(findstring leak, \$(MAKECMDGOALS)), leak)
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
else ifeq (\$(findstring thread, \$(MAKECMDGOALS)), thread)
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
else ifeq (\$(findstring debug, \$(MAKECMDGOALS)), debug)
CFLAGS = -Wall -Wextra -Werror -g3
endif
EOF


# initialize the first source file
touch src/test.c

echo "Creating the test.c file, and the main.c file"

cat <<EOF > src/main.c
#include "../libft/libft.h"

int main(void) {
	ft_printf_fd(1, "Hello From ${REPO_NAME}\n");
}
EOF



# initialize the project CI
mkdir -p .github/workflows

echo "Creating the CI file"

cat <<EOF > .github/workflows/makefile.yml
name: Makefile CI

on:
  push:
    branches: [ "main" ]
  pull_request:
    branches: [ "main" ]
  schedule:
    - cron: '0 0 * * *'

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v3
      with:
        submodules: true

    # ssh setup
    - name: Setup SSH
      uses: webfactory/ssh-agent@v0.5.3
      with:
        ssh-private-key: \${{ secrets.SSH_PRIVATE_KEY }}
    
    - name: Run make
      run: make

    - name: clean
      run: make fclean
EOF