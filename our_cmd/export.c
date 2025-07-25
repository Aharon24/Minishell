#include "../minishell.h"

void	ft_validation(char *arg, t_shell *shell)
{
	if (ft_validation_argument(arg) == 1)
		ft_add_export_or_env(shell, arg);
	else
	{
		perror("not walid");
		return ;
	}
}

void	ft_check_line_export(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	if (argv[1][0] == '_' && argv[1][1] == '\0')
		return ;
	while (argv[i])
	{
		ft_validation(argv[i], shell);
		i++;
	}
}

void	ft_sort_export(t_env *export)
{
	t_env	*e;
	t_env	*s;
	char	*tmp;
	char	*tmp_value;

	e = export;
	s = e;
	while (s->next)
	{
		if (ft_strcmp(s->key, s->next->key) > 0)
		{
			tmp = s->key;
			tmp_value = s->value;
			s->key = s->next->key;
			s->value = s->next->value;
			s->next->key = tmp;
			s->next->value = tmp_value;
			s = e;
		}
		else
			s = s->next;
	}
	ft_printf_export(e);
}

t_env	*ft_set_up_export(t_env *e, t_env *env)
{
	t_env	*start;
	t_env	*head;
	t_env	*tmp;

	start = env;
	head = new_env_node(ft_strdup(start->key), ft_strdup(start->value));
	start = start->next;
	tmp = head;
	while (start)
	{
		e = new_env_node(ft_strdup(start->key), ft_strdup(start->value));
		start = start->next;
		tmp->next = e;
		tmp = tmp->next;
	}
	return (head);
}

void	ft_export(t_shell*shell, char **argv)
{
	t_env	*e;

	e = NULL;
	if (!shell->export)
	{
		e = ft_set_up_export(e, shell->env);
		shell->export = e;
	}
	else
	{
		e = shell->export;
	}
	if (!argv[1])
	{
		ft_sort_export(e);
		return ;
	}
	else if (argv[1])
		ft_check_line_export(argv, shell);
}
