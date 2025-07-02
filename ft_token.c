#include "minishell.h"



void ft_tayp_fill_enam(char *arr, t_token *new_node)
{
	size_t len;

	len = 0;
	len = ft_strlen(arr);
	if(ft_strncmp(arr,"|",len) == 0)
		new_node->type = TOKEN_PIPE;
	else if(ft_strncmp(arr,"<",len) == 0)
		new_node->type = TOKEN_REDIRECT_IN;
	else if(ft_strncmp(arr,">",len) == 0)
		new_node->type = TOKEN_REDIRECT_OUT;
	else if(ft_strncmp(arr,">>",len) == 0)
		new_node->type = TOKEN_REDIRECT_APPEND;
	else if(ft_strncmp(arr,"<<",len) == 0)
		new_node->type = TOKEN_HEREDOC;
	else{
		new_node->type = TOKEN_WORD;
	}
}

t_token	*ft_token_fill(char **arr,t_token *l)
{
	int i;

	i = 0;
	t_token *new_node;
	t_token *head = NULL;
	t_token *last = NULL;
	while (arr[i])
	{
		new_node = ft_list_add(arr[i]);
		ft_tayp_fill_enam(arr[i],new_node);
		if (!head)
		{
			head = new_node;
			last = head;
		}    
		else
			last->next = new_node;  
		last = new_node;        
		i++;
	}
	l = head;
	return (l);
}



t_token *ft_token(char *line, t_token *l)
{
	char **arr;
	arr = ft_split(line, ' ');
	l = ft_token_fill(arr,l);
	ft_print_list(l);
	return(l);
}
