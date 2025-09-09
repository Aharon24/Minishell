/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:43 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/13 17:48:23 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	karjacum(void)
{
	g_exit_status = 2;
	return (-1);
}

int	read_all_heredocs(t_command *cmd_list)
{
	t_command	*cmd;
	int			result;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->has_heredoc = 0;
		result = read_heredocs_for_command(cmd);
		if (result != 0)
			return (result);
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
	pid_t	pid;
	int		status;
	void	(*old_handler)(int);

	if (!redir->filename || pipe(pipefd) == -1)
		return (-1);
	old_handler = signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (restore_signals(old_handler), -1);
	if (pid == 0)
		exec_heredoc_child(redir, pipefd);
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	restore_signals(old_handler);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(pipefd[0]);
		return (-2);
	}
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
