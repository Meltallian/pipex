# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = pipex_bonus
LIBFT = ../libft/libft.a
PIPEX_BONUS_SRC = main.c ft_split_2.c path.c utils.c child.c parsing.c
PIPEX_BONUS_OBJ = $(PIPEX_BONUS_SRC:.c=.o)
INCLUDES_DIR = -I../includes -I../libft
#pas necessaire parceque -lft -lmlx dans la ligne cc
# Default rule
all: $(NAME)

# This won't be called if the files don't exist or are not updated
$(PIPEX_BONUS_OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(LIBFT):
	make -C ../libft

$(NAME): $(LIBFT) $(PIPEX_BONUS_OBJ)
	$(CC) $(CFLAGS) $(PIPEX_BONUS_OBJ) -o $(NAME) -L../libft -lft

clean:
	make clean -C ../libft
	rm -f $(PIPEX_BONUS_OBJ)

fclean: clean
	make fclean -C ../libft
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

leaks: $(NAME)
	leaks --atExit -- ./$(NAME)

.PHONY: all clean fclean re run