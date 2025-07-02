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

typedef struct s_line
{
	char	*line;
	char	*get_env;
	char	**arr_get_env;
}	t_line;

///ft_list.c  (LIST)

t_token		*ft_list_add(char *data);
void		ft_print_list(t_token *l);
void		ft_print_list_enum(t_token *l);
void		ft_print_enum(t_token *l);

/// Token

t_token		*ft_token(char *line, t_token *l);
t_token		*ft_token_fill(char **arr, t_token *l);

/// fill
void		ft_tayp_fill_enam(char *arr, t_token *new_node);

///work
void		ft_token_work(t_token *l);
void		ft_token_check_and_do(t_token *chek, int flag, t_line *line);
void		ft_run_program(t_token *chek, t_line *line);
void		ft_tray_acsses(char **arr_env, t_token *chek);
char		**ft_arr_env_join_slesh(char **arr);

//// check
int			ft_strcmp(const char *str1, const char *str2);