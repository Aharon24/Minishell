#include "minishell.h"

int	main( void)
{
	t_shell shell;

	init_shell(&shell);
	run_shell(&shell);
	return (0);
	
}
