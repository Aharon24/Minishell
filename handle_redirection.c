#include "minishell.h"

int	handle_heredoc(t_redirect *redir, int *heredoc_fd)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;

		if (strcmp(line, redir->filename) == 0)
		{
			free(line);
			break;
		}

		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}

	close(pipe_fd[1]);
	*heredoc_fd = pipe_fd[0];
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;

	redir = cmd->redirects;
	while (redir)
    {
        if (redir->type == TOKEN_REDIRECT_IN)
        {
            fd = open(redir->filename, O_RDONLY);
            if (fd < 0)
            {
                perror(redir->filename);
                return -1;
            }
            dup2(fd, 0);
            close(fd);
        }
        else if (redir->type == TOKEN_REDIRECT_OUT)
        {
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(redir->filename);
                return -1;
            }
			dup2(fd, 1);
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
			dup2(fd, 1);
			close(fd);
		}
		// else if (redir->type == TOKEN_HEREDOC)
		// {
		// 	cmd->has_heredoc = 1;
		// 	if (handle_heredoc(redir, &heredoc_fd) < 0)
		// 		return (-1);
		// 	dup2(heredoc_fd, STDIN_FILENO);
		// 	close(heredoc_fd);
		// }
		redir = redir->next;
	}
	return (0);
}
