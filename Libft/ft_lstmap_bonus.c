/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmkrtch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:46:02 by asmkrtch          #+#    #+#             */
/*   Updated: 2025/02/08 18:46:04 by asmkrtch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	while (lst)
	{
		new = malloc(sizeof(t_list));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new->content = f(lst->content);
		new->next = NULL;
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}

/*#include <stdio.h>

int main()
{
    int n1;
    int n2;
    int n3;
    int n4;

    t_list *head = NULL;
    
    t_list *a1 = malloc(sizeof(t_list));
    t_list *a2 = malloc(sizeof(t_list));
    t_list *a3 = malloc(sizeof(t_list));
    t_list *a4 = malloc(sizeof(t_list));

    if (!a1 || !a2 || !a3 || !a4)
        return (1);

    n1 = 1;
    n2 = 2;
    n3 = 3;
    n4 = 4;

    a1->content = &n1;
    a1->next = NULL;
    a2->content = &n2;
    a2->next = NULL;
    a3->content = &n3;
    a3->next = NULL;
    a4->content =&n4;
    a4->next = NULL;

    ft_lstadd_back(&head, a1);
    ft_lstadd_back(&head, a2);
    ft_lstadd_back(&head, a3);
    ft_lstadd_back(&head, a4);

    printf("Размер списка: %d\n", ft_lstsize(head));

    free(a1);
    free(a2);
    free(a3);
    free(a4);

    return 0;
}*/
