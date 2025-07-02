#include <stdio.h>           	// printf, perror
#include <stdlib.h>        	 	// malloc, free, exit, getenv
#include <string.h>        	 	// strerror
#include <unistd.h>        	 	// write, access, open, read, close, fork, execve, pipe, dup, dup2, unlink, chdir, getcwd, isatty, ttyname, ttyslot
#include <sys/wait.h>      	 	// wait, waitpid, wait3, wait4
#include <signal.h>          	// signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h>        	// stat, lstat, fstat
#include <dirent.h>        	 	// opendir, readdir, closedir
#include <sys/ioctl.h>     	 	// ioctl
#include <termios.h>        	// tcsetattr, tcgetattr
#include <term.h>           	// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <readline/readline.h>  // readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
#include <readline/history.h>   // add_history


//My Libery
#include "Libft/libft.h"


typedef enum e_token_type
{
    TOKEN_WORD,       // обычное слово: команда или аргумент
    TOKEN_PIPE,       // |
    TOKEN_REDIRECT_IN,     // <
    TOKEN_REDIRECT_OUT,    // >
    TOKEN_REDIRECT_APPEND, // >>
    TOKEN_HEREDOC,         // <<
}   t_token_type;


typedef struct s_token
{
    char            *value;       // текст токена (например "cat", "file.txt", ">>")
    t_token_type     type;        // тип токена из enum
    struct s_token  *next;        // следующий токен
}   t_token;

typedef struct s_line
{
    char *line;
} t_line;
 

///ft_list.c  (LIST)

t_token *ft_list_add(char *data);
void ft_print_list(t_token *l);
void ft_print_list_enum(t_token *l);
void ft_print_enum(t_token *l);

/// Token

t_token	*ft_token(char *line,t_token *l);
t_token	*ft_token_fill(char **arr,t_token *l);
void ft_tayp_fill_enam(char *arr, t_token *new_node);