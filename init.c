#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->line = NULL;
	shell->tokens = NULL;
}
void	init_cmd(t_command *cmd)
{
	cmd->argv = NULL;
	cmd->argc = 0;
}