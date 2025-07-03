#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->line = NULL;
	shell->tokens = NULL;
}
