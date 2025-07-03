#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <term.h>
#include <readline/readline.h> 
#include <readline/history.h>

//My Libery
#include "Libft/libft.h"

typedef struct s_command {
    char **argv;
    int argc;
    struct s_command *next;
} t_command;

typedef enum e_token_type
{
	TOKEN_WORD,// обычное слово: команда или аргумент
	TOKEN_PIPE,//|
	TOKEN_REDIRECT_IN,//<
	TOKEN_REDIRECT_OUT,//>
	TOKEN_REDIRECT_APPEND,//>>
	TOKEN_HEREDOC,// <<
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*line;
	t_token	*tokens;
}	t_shell;

//add_token.c
t_token	*add_token(t_token **head, char *value, t_token_type type);

//ft_free.c
void	clear_tokens(t_token **head);
void	cleanup_loop(t_shell *shell);

//init.c
void	init_shell(t_shell *shell);

//run_shell.c
void	run_shell(t_shell *shell);

//tokenize.c
int		tokenize(t_shell *shell);
int 	lexer(char *line, t_token **tokens);
int		lex_pipe(t_token **tokens);
int		lex_redir(char *line, t_token **tokens);
int		lex_word(char *line, t_token **tokens);

//utils.c
char	*ft_strndup(char *line, int n);

//split_cmd.c
t_command *split_cmd(t_token *tokens);

#endif