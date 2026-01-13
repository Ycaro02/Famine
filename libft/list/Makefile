NAME = linked_list.a

SRC =	ft_lstadd_back.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_lstsize.c\
		ft_lstadd_front.c\
		ft_lstdelone.c\
		ft_lstlast.c\
		ft_lstnew.c\
		ft_lstjoin.c\
		ft_lstclear_nodeptr.c\
		ft_lst_remove_if.c\
		ft_lstpop.c\
		list_to_array.c\
		array_to_list.c\
		get_lst_idx_content.c\
		list_sort.c\
		reverse_lst.c \
		get_lst_node.c \

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

all : $(NAME)

%.o : %.c
	$(CC) ${CFLAGS} -c $< -o $@

$(NAME): $(OBJ)
	ar rcs -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
