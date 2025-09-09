/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:07:26 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/16 18:37:26 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include <fcntl.h>

// My Libery
# include "Libft/libft.h"

extern int	g_exit_status;

void		heredoc_sigint_handler(int signo);
void		handle_sigdfl(int signum);

typedef struct s_expand_data
{
	int		i;
	int		j;
	int		sq;
	int		dq;
	int		len;
	char	*res;
}	t_expand_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_expand_ctx
{
	char	*input;
	int		*i;
	t_env	*env;
}	t_expand_ctx;

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
	t_token_type		type;
	char				*filename;
	struct s_redirect	*next;
	int					herdok_chesk;
}	t_redirect;

typedef struct s_command
{
	char				**argv;
	t_redirect			*redirects;
	int					pip;
	int					has_heredoc;
	int					heredoc_fd;
	int					syntax_error;
	int					argc;
	struct s_command	*next;
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
	int		heredoc_interrupted;
	int		hello;
	int		ivalid_var;
}	t_shell;

//////////////OUR_CMD////////////////////////

///our_cmd/cd_2.c
void		ft_check_t(t_shell *shell, char *path);
int			ft_check_len_argv(char **argv);
int			artur(t_shell **shell, char **get_pwd, char **new);

//our_cmd/cd_helper_2.c
void		ft_resolve_pwd(char **new_pwd, t_shell *shell, char *path);
void		ft_handle_cd_dash(t_shell *shell);
void		ft_handle_cd_home(t_shell *shell);
void		ft_qsan_hing_tox(char *path);

//our_cmd/cd_helper.c
void		ft_one(char **new_pwd, t_shell *shell);
void		ft_two(char **new_pwd, t_shell *shell);
void		ft_dash(char **new_pwd, t_shell *shell);
void		ft_tilda(char **new_pwd, t_shell *shell);
void		ft_relative(char **new_pwd, t_shell *shell, char *path);

//our_cmd/cd.c
void		ft_cd_more_argument(char *path, t_shell *shell);
void		ft_cd(char **argv, t_shell *shell);
void		ft_finish(void);
void		ft_update_pwd(t_shell *shell, char *path);
void		ft_end_e(t_shell *shell, char *path);

//our_cmd/echo.c
void		ft_echo(char **argv);
int			ft_check_n_flag(char **argv, int *i);

//our_cmd/env.c
void		ft_env(t_shell *shell);

//our_cmd/export_2.c
t_env		*ft_add_export(t_env *export, char *arg);
t_env		*ft_add_env(t_env *env, char *arg);
char		*ft_ket_string(char *arg);
char		*ft_value_string(char *arg);

//our_cmd/export_3.c
int			ft_faind_key_in(t_env *e_e, char *key);
void		ft_add_export_or_env(t_shell *shell, char *arg);

//our_cmd/export_chesk.c
int			ft_validation_argument(char *arg, int i);
void		ft_printf_export(t_env *export);
char		*ft_add_env_value(char *arg);

//our_cmd/export.c
void		ft_export(t_shell*shell, char **argv);
t_env		*ft_set_up_export(t_env *e, t_env *env);
void		ft_sort_export(t_env *export);
void		ft_validation(char *str, t_shell *shell);
void		ft_check_line_export(char **argv, t_shell *shell);

//our_cmd/ft_faind_in_env.c
char		*ft_faind_in_env(t_env *env, char *argument);
char		*ft_make_path(char *str);
t_env		*ft_faind_and_change(char *argumnet, t_env *env, char *new_path);

//our_cmd/pwd.c
void		ft_pwd(t_shell *shell);
void		copy_without_quotes_and_expand(t_expand_ctx *ctx,
				t_expand_data *d, t_shell *shell);
void		handle_dollar_or_char(t_expand_ctx *ctx,
				t_expand_data *d, t_shell *shell);
// char		*remove_quotes_and_expand(char *input, t_env *env);

//our_cmd/unset.c
void		unset_env(t_env **env, char *key);
void		ft_unset(char **argv, t_shell *shell);
int			ft_faind_and_rm(char *arg, t_shell *shell);
int			ft_chesk__(char *str);

///////////////////////////////////////////////

//add_.c
t_token		*add_token(t_token **head, char *value, t_token_type type);
void		add_new_cmd(t_command **cmd_head, t_command *new_cmd);
void		add_redirect(t_redirect **head, t_redirect *new_redirect);

//ft_bild_cmd_1.c
void		ft_built_in_faind(char **argv, t_shell *shell);
int			ft_bild_cmd_out_fork(char **argv, t_shell *shell);
void		print_signal_message(int sig);
void		wait_all_and_handle(pid_t *pids, t_command **cmds, int count);
void		ft_run_cmd(t_command *cmd_list, t_shell *shell);

//ft_bild_cmd_2.c
void		ft_parent(t_command *cmd, int *prev_fd, int pipefd[2]);
void		ft_exec_or_exit(t_command *cmd, t_shell *shell);
void		ft_child(t_command *cmd, t_shell *shell,
				int pipefd[2], int prev_fd);
pid_t		ft_fork_and_manage(t_command *cmd, t_shell *shell,
				int pipefd[2], int *prev_fd);
int			ft_handle_empty_cmd(t_command *cmd);

//ft_fild_cmd_3.c
int			ft_handle_command(t_command *cmd, t_shell *shell,
				int *prev_fd, pid_t *pid_out);
void		safe_exit(int status);
int			handle_builtin_command(t_command *cmd,
				t_shell *shell, pid_t *pid_out);
int			handle_empty_command(t_command *cmd, int *prev_fd, pid_t *pid_out);
void		handle_exit_and_builtins(t_command *cmd, t_shell *shell);

// ft_bild_cmd_helper.c
int			ft_exec_cd(char **argv, t_shell *shell);
int			ft_exec_unset(char **argv, t_shell *shell);
int			ft_exec_export(char **argv, t_shell *shell);
int			ft_exec_exit(char **argv);
void		ft_init_pid(pid_t *p, t_command **cmd);

//ft_bild_cmd_helper_2.c
void		print_not_found_errors(t_command **cmds,
				int *exit_codes, int count);
void		collect_exit_codes(pid_t *pids, int *exit_codes, int count);
int			run_all_commands(t_command *cmd_list, t_shell *shell,
				pid_t *pids, t_command **cmds);
int			process_status(int wstatus);

//ft_execve_helper.c
char		*find_path(t_env *s, char *cmd);
char		*find_path_helper(char **paths, char *cmd);
char		**allocate_env_array(t_env *env, int *out_size);
void		ft_execve_error_exit(char *cmd, int code, char *msg);
int			check_command_permission(t_shell *shell, char *cmd);

//ft_exece.c
void		ft_execve(char **argv, t_shell *shell);
char		**shell_2_char(t_env *env);
char		*create_env_entry(const char *key, const char *value);
int			size_key_value(char *key, char *value);
int			size_env(t_env *env);

//export_chesk.c
char		*ft_add_env_key(char *arg);
int			ft_chesk_eqvel(char *str);

//ft_free_1.c
void		cleanup_loop(t_shell *shell);
void		free_shell(t_shell *shell);
void		free_cmd(t_command *cmd);
void		free_redirects(t_redirect *redir);
void		free_command(t_command *cmd);

////ft_free_2.c
void		ft_free_arr(char **arr);
void		free_tokens(t_token **head);
void		free_env(t_env *env);
int			check_command_and_permissions(t_shell *shell,
				t_command *cmd, pid_t *pid_out);
void		er_case(t_command *cmd);

//handle_redirection.c
int			karjacum(void);
int			handle_redirections(t_command *cmd);
int			handle_heredoc(t_redirect *redir, int *heredoc_fd);
int			read_all_heredocs(t_command *cmd_list);
int			check_redirections(t_command *cmd, int fd);

//handle_redirection_helper.c
int			foo(char *name);
int			foo2(char *name);
int			foo3(char *name);
int			read_heredocs_for_command(t_command *cmd);
void		exec_heredoc_child(t_redirect *redir, int pipefd[2]);

//handle_redirection_helper_2.c
void		heredoc_sigint_handler(int signo);
void		handle_sigdfl(int signum);
void		restore_signals(void (*old_handler)(int));
void		write_heredoc_line(int fd, char *line);

//init.c
void		init_shell(t_shell *shell, char **env);
t_env		*new_env_node(char *key, char *value);
int			init_remove_data(t_expand_data *d, char *input);

//run_shell_helper.c
int			process_tokens(t_shell *shell);
char		*read_line_or_exit(void);
void		handle_sigint(int signum);
int			process_and_execute(t_shell *shell, t_command **cmd);
void		handle_sigcat(int signum);

//run_shell.c
void		run_shell(t_shell *shell);
void		setup_signals(void);
char		*read_input(void);
int			process_line(t_shell *shell, t_command **cmd_out);

//split_cmd_2.c
int			fill_argv(t_token **tokens, t_command *new_cmd, t_shell *shell);
int			fill_redirects(t_token **tokens,
				t_command *new_cmd, t_shell *shell);
int			fill_argv_and_redirects(t_token **tokens,
				t_command *new_cmd, t_shell *shell);
int			process_redirect(t_token **tokens,
				t_command *new_cmd, t_shell *shell);

//split_cmd_3.c
char		*remove_quotes_and_expand(char *input, t_env *env, t_shell *shell);
int			handle_quotes(char *input, t_expand_data *d);
int			handle_dollar_case(t_expand_ctx *ctx,
				t_expand_data *d, t_shell *shell);

//split_cmd.c

int			size_(t_token *tokens);
int			parse_one_command(t_token **tokens,
				t_command **cmd_head, t_shell *shell);
void		new_cmd_init(t_command *new_cmd);

t_command	*split_cmd(t_token *tokens, t_shell *shell);
t_command	*allocate_new_command(t_token *tokens);

//tokenize.c
int			tokenize(t_shell *shell);
int			lexer(char *line, t_token **tokens);
int			lex_pipe(t_token **tokens);
int			lex_redir(char *line, t_token **tokens);
int			lex_word(char *line, t_token **tokens);

///utils_2.c
char		*ft_strndup(char *line, int n);
int			ft_check_exit_cmd(char **argv);
int			ft_ch(char *arr);
int			extract_key_value(char *env_entry, char **key, char **value);
void		free_env_array(char **env_arr, int count);

//utils.c
int			ft_strcmp(char *s1, char *s2);
char		*get_env_value(char *key, t_env *env);
int			copy_var_value(char *res, int j, t_expand_ctx *ctx, t_shell *shell);
void		print_str(const char *str);
int			ft_handle_exit_cmd(char **argv);

//validation_tokens.c
int			is_redirection(t_token_type type);
int			check_pipe_error(t_token *token);
int			check_redirection_error(t_token *token);
int			validate_tokens(t_token *tokens);

#endif