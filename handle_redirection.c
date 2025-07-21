#include "minishell.h"

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
		else if (redir->type == TOKEN_HEREDOC)
		{
			//pipe
		}
		redir = redir->next;
	}
	return (0);
}
