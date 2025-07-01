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


typedef struct s_s
{
	char	*line;
	char	**arr;
	char	*path_env;
	char	**orignal_path;
}	t_s_list;

void	ft_first_step(t_s_list *s);