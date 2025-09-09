/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahapetro <ahapetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:06:47 by ahapetro          #+#    #+#             */
/*   Updated: 2025/08/16 18:37:55 by ahapetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

// void	print_env(t_env *env)
// {
// 	while (env)
// 	{
// 		printf("ENV: %s=%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }

// void	print_shell(t_shell *shell)
// {
// 	printf("=== SHELL STRUCT ===\n");

// 	if (shell->line)
// 		printf("Line: \"%s\"\n", shell->line);
// 	else
// 		printf("Line: (null)\n");

// 	printf("\n--- Tokens ---\n");
// 	print_tokens(shell->tokens);

// 	printf("\n--- Environment ---\n");
// 	print_env(shell->env);

// 	//printf("\nOld path: %s\n", shell->old_path ? shell->old_path : "(null)");
// 	//printf("Home path: %s\n", shell->home ? shell->home : "(null)");

// 	printf("====================\n");
// }

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (127);
	}
	init_shell(&shell, env);
	run_shell(&shell);
	return (g_exit_status);
}
