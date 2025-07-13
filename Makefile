NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror  

LIBFT_DIR = Libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LDFLAGS = -lreadline

 
SRC = main.c\
	add_.c\
	ft_free.c\
	init.c\
	run_shell.c\
	tokenize.c\
	handle_redirection.c\
	utils.c\
	split_cmd.c\
	our_cmd/cd.c\
	our_cmd/pwd.c\
	our_cmd/unset.c\
	our_cmd/env.c\
	ft_bild_cmd.c\
	our_cmd/ft_faind_in_env.c\
	our_cmd/cd_2.c\
	our_cmd/export.c\
	our_cmd/export_2.c\
	our_cmd/export_chesk.c\
	#uor_cmd/echo.c
 
OBJ = $(SRC:.c=.o)

 
all: $(NAME)
 
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)
 
$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR)  $(LDFLAGS) -lft -o $(NAME)

 
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
