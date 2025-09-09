NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = Libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LDFLAGS = -lreadline

SRC = main.c \
	add_.c \
	ft_free_1.c \
	init.c \
	run_shell.c \
	tokenize.c \
	handle_redirection.c \
	handle_redirection_helper.c \
	handle_redirection_helper_2.c \
	validation_tokens.c \
	utils.c \
	utils_2.c \
	split_cmd.c \
	split_cmd_2.c \
	split_cmd_3.c \
	our_cmd/cd.c \
	our_cmd/pwd.c \
	run_shell_helper.c \
	ft_bild_cmd_helper_2.c \
	our_cmd/unset.c \
	our_cmd/env.c \
	ft_bild_cmd_1.c \
	ft_bild_cmd_2.c \
	ft_bild_cmd_3.c \
	ft_bild_cmd_helper.c \
	our_cmd/ft_faind_in_env.c \
	our_cmd/cd_2.c \
	our_cmd/cd_helper_2.c \
	our_cmd/cd_helper.c \
	our_cmd/export.c \
	our_cmd/export_2.c \
	our_cmd/export_3.c \
	our_cmd/export_chesk.c \
	ft_execve.c \
	ft_execve_helper.c \
	our_cmd/echo.c \
	ft_free_2.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A): $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LDFLAGS) -lft -o $(NAME)

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
