#include "minishell.h"

void	ft_token_work(t_token *l)
{
	t_token	*run;
	t_line	line;
	int		i;

	i = 1;
	run = l;
	while (run)
	{
		ft_token_check_and_do(run, i, &line);
		run = run->next;
		i++;
	}
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (!str1 ||!str2)
		return (1);
	while (str1[i] == str2[i] && str1[i])
		i++;
	return (str1[i] - str2[i]);
}

void	ft_tayp_fill_enam(char *arr, t_token *new_node)
{
	if (ft_strcmp(arr, ">>") == 0)
		new_node->type = TOKEN_REDIRECT_APPEND;
	else if (ft_strcmp(arr, "<<") == 0)
		new_node->type = TOKEN_HEREDOC;
	else if (ft_strcmp(arr, "|") == 0)
		new_node->type = TOKEN_PIPE;
	else if (ft_strcmp(arr, "<") == 0)
		new_node->type = TOKEN_REDIRECT_IN;
	else if (ft_strcmp(arr, ">") == 0)
		new_node->type = TOKEN_REDIRECT_OUT;
	else
		new_node->type = TOKEN_WORD;
}

t_token	*ft_token_fill(char **arr, t_token *l)
{
	int		i;
	t_token	*new_node;
	t_token	*head;
	t_token	*last;

	i = 0;
	head = NULL;
	last = NULL;
	while (arr[i])
	{
		new_node = ft_list_add(arr[i]);
		ft_tayp_fill_enam(arr[i], new_node);
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

t_token	*ft_token(char *line, t_token *l)
{
	char	**arr;

	arr = NULL;
	arr = ft_split(line, ' ');
	l = ft_token_fill(arr, l);
	ft_token_work(l);
	//ft_print_list(l);
	return (l);
}
