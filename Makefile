
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline

LIBFT_DIR = Libft
LIBFT_A = $(LIBFT_DIR)/libft.a

 
SRC = main.c ft_first_step.c 
 
OBJ = $(SRC:.c=.o)

 
all: $(NAME)
 
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)
 
$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

 
%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

 
clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

 
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
