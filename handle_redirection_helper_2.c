/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_helper_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:54:36 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/08 19:16:49 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	write(1, ">\n", 3);
	exit(130);
}

void	handle_sigdfl(int signum)
{
	(void)signum;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	restore_signals(void (*old_handler)(int))
{
	signal(SIGINT, old_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}
