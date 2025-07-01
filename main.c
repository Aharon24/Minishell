#include "minishell.h"

int	main( void)
{
	t_s_list	s;
	t_token		l;

	l.next = NULL;
	while (1)
	{
		s.line = readline("---minishell->");
		ft_token(s.line,&l);
	}
	//ft_print_list(&l);
}
