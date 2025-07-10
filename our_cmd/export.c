#include "../minishell.h"

void ft_set_up_export(t_export *e,t_env *e)
{

}
void ft_export(t_shell*shell)
{
	t_export *e;

	ft_set_up_export(e,shell->env);

}