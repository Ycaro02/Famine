# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    source.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 16:54:20 by nfour             #+#    #+#              #
#    Updated: 2025/01/31 15:38:39 by nfour            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM 			= rm -rf

OBJ_DIR		=	obj

LIBFT_DIR	=	libft/

LIBFT_SRC 	=	ft_memset.c \
				ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_split.c \
				ft_strchr.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strdup.c \
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_ltoa.c \
				ft_free_tab.c \
				ft_strjoin_free.c \
				ft_lower_strcmp.c \
				ft_strcmp.c \
				ft_strcpy.c\
				get_next_line.c \
				str_is_digit.c\
				handle_double_char_array.c\
				ft_atof.c\
				ft_split_trim.c\
				check_struct_size.c\
				str_tolower.c\
				ft_fast_str.c \
				utils.c\


PRINTF_FD_DIR	=	printf_fd

PRINTF_FD_SRC	=	ft_intfunction.c \
					ft_printf.c \
					ft_put_and_count.c \

PARSE_FLAG_DIR	=	parse_flag

PARSE_FLAG_STR	=	parse_flag.c \
					handle_flag.c \
					parse_cmd_line.c \
					handle_option.c \

STACK_STRING_DIR	=	stack_string

STACK_STRING_SRC	=	stack_string.c \
						sstring_gnl.c\


MATH_DIR			=	math

MATH_SRC			=	basic_math.c


HASHMAP_DIR			=	HashMap

HASHMAP_SRC			=	HashMap.c\

BMP_PARSER_DIR		=	BMP_parser

BMP_PARSER_SRC		=	parse_bmp.c\
						image_cut.c\


ALL_OBJ_DIR = 	$(OBJ_DIR)/libft\
				$(OBJ_DIR)/$(PRINTF_FD_DIR)\
				$(OBJ_DIR)/$(PARSE_FLAG_DIR)\
				$(OBJ_DIR)/$(STACK_STRING_DIR)\
				$(OBJ_DIR)/$(MATH_DIR)\
				$(OBJ_DIR)/$(HASHMAP_DIR)\
				$(OBJ_DIR)/$(BMP_PARSER_DIR)\

				
SRCS =	$(addprefix ${LIBFT_DIR}, $(LIBFT_SRC)) \
		$(addprefix $(PRINTF_FD_DIR)/, $(PRINTF_FD_SRC)) \
		$(addprefix $(PARSE_FLAG_DIR)/, $(PARSE_FLAG_STR)) \
		$(addprefix $(STACK_STRING_DIR)/, $(STACK_STRING_SRC)) \
		$(addprefix $(MATH_DIR)/, $(MATH_SRC)) \
		$(addprefix $(HASHMAP_DIR)/, $(HASHMAP_SRC)) \
		$(addprefix $(BMP_PARSER_DIR)/, $(BMP_PARSER_SRC)) \


OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
