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

// My Libery
#include "Libft/libft.h"

extern int g_exit_status;
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
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
	int	has_heredoc;
	int	heredoc_fd;
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
	t_env	*env; //free
	t_env	*export;
	char	*home_chesk;
	char	*home;
	char	*pwd;
	char	*old_path;
	char	*temp;
	int		len;
	int		exit_i;
	int		check_exit;
}	t_shell;

//add_.c
t_token	*add_token(t_token **head, char *value, t_token_type type);
void	add_new_cmd(t_command **cmd_head, t_command *new_cmd);
void	add_redirect(t_redirect **head, t_redirect *new_redirect);

//ft_free.c
void	free_tokens(t_token **head);
void	cleanup_loop(t_shell *shell);
void	free_shell(t_shell *shell);
void	free_env(t_env *env);
void	free_cmd(t_command *cmd);
void	free_redirects(t_redirect *redir);
void	free_command(t_command *cmd);

////ft_free_2.c
void ft_free_arr(char **arr);

//init.c
void	init_shell(t_shell *shell, char **env);
t_env	*new_env_node(char *key, char *value);

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
int		handle_heredoc(t_redirect *redir, int *heredoc_fd);

//utils.c
char	*ft_strndup(char *line, int n);
int		ft_strcmp(char *s1, char *s2);
char	*get_env_value(char *key, t_env *env);
char	*remove_quotes_and_expand(char *input, t_env *env);
int		copy_var_value(char *res, int j, char *input, int *i, t_env *env);

///utils_2.c
int	ft_check_exit_cmd(char **argv);
int	ft_ch(char *arr);

//split_cmd.c
t_command *split_cmd(t_token *tokens, t_shell *shell);

//our_cmd/pwd.c
void ft_pwd(char **argv);

//our_cmd/cd.c
void ft_cd_more_argument(char  *path, t_shell *shell);
void ft_cd(char **argv, t_shell *shell);
void ft_finish(void);
void ft_update_pwd(t_shell *shell);
void ft_end_e(t_shell *shell, char *path);
//// [5]

///our_cmd/cd_2.c
void ft_check_t(t_shell *shell, char *path);
int	ft_check_len_argv(char **argv);

//our_cmd/unset.c
void	unset_env(t_env **env, char *key);
void	ft_unset(char **argv, t_shell *shell);
int		ft_faind_and_rm(char *arg, t_shell *shell);
int		ft_chesk__(char *str);


//our_cmd/env.c
void	ft_env(t_shell *shell);

//our_cmd/export.c
void	ft_export(t_shell*shell, char **argv);
t_env	*ft_set_up_export(t_env *e,t_env *env);
void	ft_sort_export(t_env *export);
void	ft_validation(char *str, t_shell *shell);
void	ft_check_line_export(char **argv, t_shell *shell);
//void	ft_check_line_export(char *arr);

//our_cmd/export_2.c
void	ft_add_export_or_env(t_shell *shell, char *arg);
t_env	*ft_add_export(t_env *export, char *arg);
t_env	*ft_add_env(t_env *env, char *arg);
char	*ft_ket_string(char *arg);
char	*ft_value_string(char *arg);

//our_cmd/export_3.c
int ft_faind_key_in(t_env *e_e, char *key);

//our_cmd/echo.c
void	ft_echo(char **argv);

//our_cmd/export_chesk.c
int	ft_validation_argument(char *arg, int i);
void	ft_printf_export(t_env *export);
char	*ft_add_env_value(char *arg);

///ft_exece.c
void	ft_execve(char **argv, t_shell *shell);
char	*find_path_helper(char **paths, char *cmd);
char	*find_path(t_env *s, char *cmd);
char	*ft_add_env_key(char *arg);
int 	ft_chesk_eqvel(char *str);
char	**shell_2_char(t_env *env);


//ft_bild_cmd.c
void	ft_run_cmd(t_command *cmd, t_shell *shell);
void	ft_built_in_faind(char **argv, t_shell *shell);
int		ft_bild_cmd_out_fork(char **argv,t_shell *shell);

///ft_faind_in_env.c
char	*ft_faind_in_env(t_env *env, char *argument);
char	*ft_make_path(char *str);
t_env	*ft_faind_and_change(char *argumnet, t_env *env, char *new_path);

// ft_main.c
void	handle_sigcat(int signum);

#endif