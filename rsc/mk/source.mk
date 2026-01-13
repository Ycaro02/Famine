CFLAGS			=	-Wall -Wextra -Werror -O3 -I include

OBJ_DIR			=	obj

ALL_SRC_DIR 	=	obj \
					obj/log

SRC_DIR 		=	src

MAIN_MANDATORY 	=	main.c

SRCS			=	log/log.c \
					elf_getter.c \
					parse_elf_file.c \
					signature.c \
					utils.c \
					boot_start.c \
					check_process.c \
					counter_debug.c

MAKE_LIBFT		=	make -s -C libft -j

MAKE_LIST		=	make -s -C libft/list -j

LIBFT			= 	libft/libft.a

LIST			= 	libft/list/linked_list.a

OBJS 			= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

RM			=	rm -rf

WOODY_SRC_DIR = obj/woody \
				obj/woody/asm \

C_WOODY_SRCS =	woody/encrypt_keygen.c \
				woody/function_to_opcodes.c \
				woody/handle_strtab.c \
				woody/init_bonus.c \
				woody/load_segment.c \
				woody/parse_elf_header.c \
				woody/payload.c \
				woody/woody_utils.c \
				woody/woody_woodpacker.c \
				woody/main.c \

ASM_SRCS		=	woody/asm/encrypt_data.s \
					woody/asm/decrypt_data_exec.s \
					woody/asm/decrypt_data.s \


ASM_OBJS		= $(addprefix $(OBJ_DIR)/, $(ASM_SRCS:.s=.o))


ifeq ($(findstring bonus, $(MAKECMDGOALS)), bonus)
ASCII_NAME	= "bonus"
SRCS += $(C_WOODY_SRCS)
ALL_SRC_DIR += $(WOODY_SRC_DIR)
CFLAGS += -DFAMINE_BONUS -DWOODY_BONUS -DDYNAMIC_32_BITS_ENTRY
SRCS += $(MAIN_MANDATORY)
else
SRCS += $(MAIN_MANDATORY)
endif

ifeq ($(findstring leak, $(MAKECMDGOALS)), leak)
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
else ifeq ($(findstring thread, $(MAKECMDGOALS)), thread)
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
else ifeq ($(findstring debug, $(MAKECMDGOALS)), debug)
CFLAGS = -Wall -Wextra -Werror -g3
endif
