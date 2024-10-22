NAME = pipex

SRC = src/main.c src/misc.c src/utils.c

LIBFT = libft/libft.a

GNL	=	gnl/get_next_line.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(GNL) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) -o $(NAME) -g

$(GNL):
	@make -C gnl

$(LIBFT):
	@make -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@make clean -C gnl
	@make clean -C libft
	@rm -rf *.o

fclean: clean
	@make fclean -C gnl
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re