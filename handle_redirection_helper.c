/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:42 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/08 20:05:12 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	foo(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror(name);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	foo2(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(name);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	foo3(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(name);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	read_heredocs_for_command(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;
	int			res;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (!redir->filename)
				return (karjacum());
			res = handle_heredoc(redir, &fd);
			if (res == -2)
				return (-2);
			if (res < 0)
				return (-1);
			cmd->heredoc_fd = fd;
			cmd->has_heredoc = 1;
		}
		redir = redir->next;
	}
	return (0);
}

void	exec_heredoc_child(t_redirect *redir, int pipefd[2])
{
	char	*line;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(130);
		if (ft_strcmp(line, redir->filename) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipefd[1], line);
	}
	close(pipefd[1]);
	exit(0);
}
