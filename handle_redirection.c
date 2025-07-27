#include "minishell.h"

int	handle_heredoc(t_redirect *redir, int *heredoc_fd)
{
	int		pipefd[2];
	char	*line;

	if (!redir->filename)
		return (-1);
	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->filename) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	*heredoc_fd = pipefd[0];
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN && !cmd->has_heredoc)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0)
			{
				perror(redir->filename);
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
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
			dup2(fd, STDOUT_FILENO);
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
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}
