NAME    =   libftprintf.a

SRC     =   ft_printf.c             \
            ft_decimal_unsigned_int.c \
            ft_puthexnbr.c          \
            ft_putpointer.c         \
            libft_with_counter.c

OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
AR = ar crs

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
