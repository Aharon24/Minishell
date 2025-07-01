#include "minishell.h"

int	main( void)
{
	t_s_list	s;

	while (1)
	{
		s.line = readline("---minishell->");
		ft_first_step(&s);
	}
}
