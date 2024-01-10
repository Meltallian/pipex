# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = pipex
LIBFT = libft/libft.a
pipex_SRC = main.c asc_int.c clean.c atoi_mod.c ope_s_p.c utils.c \
				ope_r.c ope_rr.c algo.c move_b.c small_a.c stack_utils.c \
				rota_a.c rota_b.c calculus.c
pipex_OBJ = $(pipex_SRC:.c=.o)
#INCLUDES_DIR = -I./includes -I./libft/includes -I./minilibx_macos/includes
#pas necessaire parceque -lft -lmlx dans la ligne cc
# Default rule
all: $(NAME)

# This won't be called if the files don't exist or are not updated
$(pipex_OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(LIBFT):
	make -C ./libft

$(NAME): $(LIBFT) $(pipex_OBJ)
	$(CC) $(CFLAGS) $(pipex_OBJ) $(LIBFT) -o $(NAME) -L./libft -lft

clean:
	make clean -C ./libft
	rm -f $(pipex_OBJ)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

leaks: $(NAME)
	leaks --atExit -- ./$(NAME)

.PHONY: all clean fclean re run