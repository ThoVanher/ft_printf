NAME = libftprintf.a

SRCS = lib3.c ft_printf.c ft_linked_list.c verif_create_free.c fill_up_lst.c fill_up_lst2.c fill_up_lst3.c display_d.c display_u.c display_c.c display_s.c display_pourcent.c display_x.c convert_base_x.c display_ptr.c convert_base_ptr.c lib.c lib2.c

OBJS = $(SRCS:.c=.o)

INCLUDE = -I include

CC = gcc $(CFLAGS) $(INCLUDE)
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra 

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean : 
	make clean -C libft
	$(RM) $(OBJS)

fclean : clean 
	make fclean -C libft
	$(RM) $(NAME)

re : fclean all

.PHONY : re clean fclean all
