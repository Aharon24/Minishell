#include "minishell.h"

// void	ft_first_step(t_s_list *s)
// {
// 	int	i;

// 	i = 0;
// 	s->path_env = getenv("PATH");
// 	s->orignal_path = ft_split(s->path_env, ':');
// 	while(s->orignal_path[i])
// 	{
// 		printf("%s\n",s->orignal_path[i]);
// 		i++;
// 	}
// 	s->arr = ft_split(s->line, ' ');
// 	if (access(s->arr[0], X_OK) == 0)
// 		printf("OK\n");
// }


void ft_token(char *line, t_token *l)
{
	int i = 0;
	char **arr;
	t_token *head = NULL;
	t_token *last = NULL;
	t_token *new_node;

	arr = ft_split(line, ' ');
	while (arr[i])
	{
		new_node = ft_list_add(arr[i]);
		if (!head)
			head = new_node;    
		else
			last->next = new_node;  
		last = new_node;        
		i++;
	}
	l = head;
	ft_print_list(head);
}




