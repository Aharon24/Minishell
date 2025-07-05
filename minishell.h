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
#include <fcntl.h>

//My Libery
#include "Libft/libft.h"

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef enum e_token_type
{
	TOKEN_WORD,// обычное слово: команда или аргумент
	TOKEN_PIPE,//|
	TOKEN_REDIRECT_IN,//<
	TOKEN_REDIRECT_OUT,//>
	TOKEN_REDIRECT_APPEND,//>>
	TOKEN_HEREDOC,// <<
}	t_token_type;

typedef struct s_redirect
{
	t_token_type	type;
	char			*filename;
	struct s_redirect *next;
}	t_redirect;

typedef struct s_command
{
	char **argv;
	t_redirect *redirects;
	int pip;
	struct s_command *next;
}	t_command;

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
	t_env	*env;
	char	*old_path;
	char	*home;
}	t_shell;

//add_.c
t_token	*add_token(t_token **head, char *value, t_token_type type);
void	add_new_cmd(t_command **cmd_head, t_command *new_cmd);
void	add_redirect(t_redirect **head, t_redirect *new_redirect);

//ft_free.c
void	clear_tokens(t_token **head);
void	cleanup_loop(t_shell *shell);

//init.c
void	init_shell(t_shell *shell, char **env);

//run_shell.c
void	run_shell(t_shell *shell);
void	print_tokens(t_token *tokens);

//tokenize.c
int		tokenize(t_shell *shell);
int 	lexer(char *line, t_token **tokens);
int		lex_pipe(t_token **tokens);
int		lex_redir(char *line, t_token **tokens);
int		lex_word(char *line, t_token **tokens);

//handle_redirection.c
int		handle_redirections(t_command *cmd);

//utils.c
char	*ft_strndup(char *line, int n);

//split_cmd.c
t_command *split_cmd(t_token *tokens);

//our_cmd/pwd.c
void ft_pwd(void);

//our_cmd/cd.c
void ft_cd_more_argument(char *old_pwd,char  *path);
void ft_cd(char **argv, t_shell *shell);

//built_in_faind_my.c
void	ft_run_cmd(t_command *cmd, t_shell *shell);
void	ft_built_in_faind(char **argv, t_shell *shell);

#endif