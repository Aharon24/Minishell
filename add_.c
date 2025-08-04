/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:03 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/04 20:06:04 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*last;

	if (!value)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}

void	add_new_cmd(t_command **cmd_head, t_command *new_cmd)
{
	t_command	*last;

	if (!(*cmd_head))
	{
		*cmd_head = new_cmd;
	}
	else
	{
		last = *cmd_head;
		while (last->next)
			last = last->next;
		last->next = new_cmd;
	}
}

void	add_redirect(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*tmp;

	if (!head || !new_redirect)
		return ;
	if (!*head)
	{
		*head = new_redirect;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redirect;
	}
}
