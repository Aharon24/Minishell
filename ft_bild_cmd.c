#include "minishell.h"

void	ft_built_in_faind(char **argv)
{
    if (ft_strncmp(argv[0], "cd", 2) == 0)
        ft_cd(argv);
    else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd();
    // else if (ft_strncmp(argv[0], "env", 3) == 0)
	// 	ft_env();
	// else if (ft_strncmp(argv[0], "export", 6) == 0)
	// 	ft_export();
	// else if (ft_strncmp(argv[0], "unset", 5) == 0)
	// 	ft_unset();
	// else if (ft_strncmp(argv[0], "echo", 4) == 0)
	// 	ft_echo();
	// else if (ft_strncmp(argv[0], "exit", 4) == 0)
	// 	ft_exit();
	// else
	// 	ft_execve();
}


void ft_run_cmd(t_command *cmd)
{
    while(cmd)
    {
        ft_built_in_faind(cmd->argv);
        cmd = cmd->next;
    }
}