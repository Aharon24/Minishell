#include "../minishell.h"


// void	ft_check_line_export(char *arr)
// {

void ft_print_export(t_env *export)
{
	t_env	*e;
	t_env	*s;
	char	*tmp;

	e = export;
	s = e;
	while (s->next)
	{
		if (ft_strcmp(s->key,s->next->key) > 0)
		{
			tmp = s->key;
			s->key = s->next->key;
			s->next->key =  tmp;
			s = e;
		}
		else
			s = s->next;
	}
	while (e)
	{
		printf("declare -x %s=%s\n", e->key, e->value);
		e = e->next;
	}
}



t_env	*ft_set_up_export(t_env *e,t_env *env)
{
	t_env *start;
	t_env *head;
	t_env *tmp;

	start = env;
	head = new_env_node(ft_strdup(start->key),ft_strdup(start->value));
	start = start->next;
	tmp = head;
	while (start)
	{
		e = new_env_node(ft_strdup(start->key),ft_strdup(start->value));
		start = start->next;
		tmp->next = e;
		tmp = tmp->next;

	}
	return (head);
}
void ft_export(t_shell*shell, char **argv)
{
	t_env	*e;

	e = NULL;
	e = ft_set_up_export(e, shell->env);
	if (!argv[1])
	{
		ft_print_export(e);
		return ;
	}
	else if(argv[2])
	{
		perror("To may Argument");
		return ;
	}
	else if(argv[1])
	{
		//ft_check_line_export(argv[1]);
		return ;
	}
	shell->export = e;
}