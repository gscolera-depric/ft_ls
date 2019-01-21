NAME=libftprintf.a
SRC=ft_printf.c src/*.c manages/*.c libft/*.c
INCLUDES=includes/
OBJ=*.o

$(NAME):
	@gcc -c $(SRC) -I $(INCLUDES)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
all: $(NAME)
test:
	@gcc $(SRC) main.c -I $(INCLUDES)
clean:
	@/bin/rm -f	$(OBJ)
fclean: clean
	@/bin/rm -f $(NAME)
re: fclean $(NAME)
