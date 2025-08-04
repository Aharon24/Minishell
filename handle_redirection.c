/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:43 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:06:44 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	karjacum(void)
{
	ft_putstr_fd("minishell: syntax error near "
		"unexpected token `newline'\n", 2);
	return (-1);
}

int	read_all_heredocs(t_command *cmd_list)
{
	t_command	*cmd;
	t_redirect	*redir;
	int			fd;

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
					return (karjacum());
				if (handle_heredoc(redir, &fd) < 0)
					return (-1);
				cmd->heredoc_fd = fd;
				cmd->has_heredoc = 1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	check_redirections(t_command *cmd, int fd)
{
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == TOKEN_REDIRECT_OUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_REDIRECT_APPEND)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			redir = redir->next;
			continue ;
		}
		if (fd < 0)
		{
			perror(redir->filename);
			return (-1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}

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
			break ;
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

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN && !cmd->has_heredoc)
		{
			if (foo(redir->filename) == -1)
				return (-1);
		}
		else if (redir->type == TOKEN_REDIRECT_OUT)
		{
			if (foo2(redir->filename) == -1)
				return (-1);
		}
		else if (redir->type == TOKEN_REDIRECT_APPEND)
		{
			if (foo3(redir->filename) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
