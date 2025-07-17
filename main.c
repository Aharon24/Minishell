#include "minishell.h"

int g_exit_status = 0;

void	print_env(t_env *env)
{
	while (env)
	{
		printf("ENV: %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_shell(t_shell *shell)
{
	printf("=== SHELL STRUCT ===\n");

	if (shell->line)
		printf("Line: \"%s\"\n", shell->line);
	else
		printf("Line: (null)\n");

	printf("\n--- Tokens ---\n");
	print_tokens(shell->tokens);

	printf("\n--- Environment ---\n");
	print_env(shell->env);

	//printf("\nOld path: %s\n", shell->old_path ? shell->old_path : "(null)");
	//printf("Home path: %s\n", shell->home ? shell->home : "(null)");

	printf("====================\n");
}

int	main(int argc, char **argv, char **env)
{
	t_shell shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	//print_shell(&shell);
	run_shell(&shell);
	return (0);
	
}
