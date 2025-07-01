/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dt_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:30:21 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/08 16:30:24 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}
/*#include <stdio.h>

void 	ft_print_(t_list *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

int	main()
{
	char *s1 = "Hello";
	char *s2 = "my";
	char *s3 = "friend";

	t_list	*head;

	head = NULL;

	t_list	*a1;
	t_list	*a2;
	t_list	*a3;
	t_list	*a4;

	a1 = (t_list *)malloc(sizeof(t_list));
	a2 = (t_list *)malloc(sizeof(t_list));
	a3 = (t_list *)malloc(sizeof(t_list));

	if(!a1 || !a2 || !a3)
		return (1);

	a1->content = s1;
	a2->content = s2;
	a3->content = s3;

	ft_lstadd_back(&head, a1);
	ft_lstadd_back(&head, a2);
	ft_lstadd_back(&head, a3);

	ft_print_(head);

	free(a1);
	free(a2);
	free(a3);
}*/