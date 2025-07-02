#include "minishell.h"

int	main( void)
{
	t_token		*l;
	t_line		s;

	l = NULL;
	while (1)
	{
		s.line = readline("---minishell-> ");
		l = ft_token(s.line, l);
		//ft_print_enum(l);
	}
	//t_print_list_enum(&l);
}
