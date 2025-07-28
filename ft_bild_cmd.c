#include "minishell.h"

int	ft_bild_cmd_out_fork(char **argv,t_shell *shell)
{
	if (ft_strncmp(argv[0], "cd",2) == 0)
	{
        ft_cd(argv, shell);
		return (1);
	}
	else if (ft_strncmp(argv[0], "unset",5) == 0)
	{
		ft_unset(argv, shell);
		return (1);
	}
	else if (ft_strncmp(argv[0], "export",6) == 0)
	{
		ft_export(shell,argv);
		return (1);
	}
	else 
		return (0);
}


void	ft_built_in_faind(char **argv, t_shell *shell)
{
    if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd(argv);
    else if (ft_strncmp(argv[0], "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(argv[0], "echo", 4) == 0)
		ft_echo(argv);
	else 
		ft_execve(argv, shell);
}

int	read_all_heredocs(t_command *cmd_list)
{
	t_command	*cmd;
	t_redirect	*redir;
	int			heredoc_fd;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->has_heredoc = 0;
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				if (!redir->filename)
				{
					ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
					return (-1);
				}
				if (handle_heredoc(redir, &heredoc_fd) < 0)
					return (-1);
				cmd->heredoc_fd = heredoc_fd;
				cmd->has_heredoc = 1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	check_redirections(t_command *cmd)
{
	t_redirect *redir;
	int fd;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->filename);
				return (-1);
			}
			close(fd);
		}
		else if (redir->type == TOKEN_REDIRECT_OUT)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redir->filename);
				return (-1);
			}
			close(fd);
		}
		else if (redir->type == TOKEN_REDIRECT_APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror(redir->filename);
				return (-1);
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}


void print_str(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    write(2, str, len);
}

void print_signal_message(int sig)
{
    if (sig == 11)
        print_str("Segmentation fault\n");
    else if (sig == 2)
        write(1, "\n", 1);
    else if (sig == 3)
        print_str("Quit\n");
    else if (sig == 13)
        ;
    else
    {
    }
}

void wait_all_and_handle(void)
{
    int wstatus;
    pid_t pid;

    while ((pid = wait(&wstatus)) > 0)
    {
        if ((wstatus & 0x7f) != 0)
        {
            int sig = wstatus & 0x7f;
            print_signal_message(sig);
            if (sig != 13) // не SIGPIPE
                g_exit_status = 128 + sig;
        }
        else 
        {
            g_exit_status = (wstatus >> 8) & 0xff;
        }
    }
}

void ft_run_cmd(t_command *cmd_list, t_shell *shell)
{
    t_command *cmd = cmd_list;
    int pipefd[2];
    int prev_fd = -1;
    pid_t pid;

    if (read_all_heredocs(cmd_list) == -1)
        return;

    while (cmd)
    {
        int is_pipe = cmd->pip;

        if (!cmd->argv || !cmd->argv[0])
        {
            if (cmd->has_heredoc)
                close(cmd->heredoc_fd);
            if (check_redirections(cmd) == -1)
                g_exit_status = 1;
            cmd = cmd->next;
            continue;
        }

        if (check_redirections(cmd) == -1)
        {
            cmd = cmd->next;
            continue;
        }

        if (ft_bild_cmd_out_fork(cmd->argv, shell) == 1)
        {
            cmd = cmd->next;
            continue;
        }

        if (is_pipe && pipe(pipefd) < 0)
        {
            perror("pipe");
            return;
        }

        pid = fork();
        signal(SIGINT, handle_sigcat);
        signal(SIGQUIT, SIG_DFL);
        if (pid == 0)
        {

            if (is_pipe)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            if (cmd->has_heredoc)
                dup2(cmd->heredoc_fd, STDIN_FILENO);
            else if (prev_fd != -1)
                dup2(prev_fd, STDIN_FILENO);

            if (handle_redirections(cmd) == -1)
                _exit(1);

            if (ft_strcmp(cmd->argv[0], "exit") == 0)
            {
                int status = ft_check_exit_cmd(cmd->argv);
                if (status == 257)
                {
                    write(2, "exit: too many arguments\n", 26);
                    _exit(1);
                }
                else if (status == 258)
                {
                    write(2, "exit: numeric argument required\n", 33);
                    _exit(2);
                }
                _exit(status);
            }

            ft_built_in_faind(cmd->argv, shell);
            _exit(g_exit_status);
        }
        else if (pid > 0)
        {
            if (prev_fd != -1)
                close(prev_fd);

            if (is_pipe)
            {
                close(pipefd[1]);
                prev_fd = pipefd[0];
            }
            else
                prev_fd = -1;

            if (cmd->has_heredoc)
                close(cmd->heredoc_fd);
        }
        else
        {
            perror("fork");
            return;
        }
        cmd = cmd->next;
    }

    wait_all_and_handle();
}