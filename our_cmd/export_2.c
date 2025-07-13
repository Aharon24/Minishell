// #include "../minishell.h"

// void	ft_add_export_or_env(t_shell *shell, char *arg)
// {
//     int i;

//     i = 0;
// 	shell->temp = ft_strdup("1");
//     while (arg[i] && arg[i] != '=')
//         i++;
//     if (arg[i] != '=')
// 	{
// 		ft_add_export(shell->export, arg);
// 	}
// 	else if (arg[i] == '=' && arg[i + 1] == '\0')
// 	{
// 		ft_add_export(shell->export, arg);
// 		//ft_add_env(shell->env, arg);
// 	}
// 	else
// 	{
// 		ft_add_export(shell->export, arg);
// 		//ft_add_env(shell->env, arg);
// 	}
// }

// void ft_add_export(t_env *export, char *arg)
// {
// 	t_env	*start;
// 	char	*key;
// 	//char	*value;
//     if (!export || !export->next)
// 		return ;
// 	start = export;
//     while (start->next)
// 		start = start->next;
// 	key = ft_ket_string(arg);
//     printf("key %s\n ",key);
// 	//value = ft_value_string(arg);

// 	//start->next = new_env_node(key, value);
// }
// // void ft_add_env(t_env, char *arg)
// // {

// // }

// char *ft_ket_string(char *arg)
// {
//     int i;
//     char *new;

//     i = 0;
//     while(arg[i] && arg[i] != '=')
//         i++;
//     new = malloc((i + 1) * sizeof(char));
//     i = 0;
//     while(arg[i] && arg[i] != '=')
//     {
//         new[i] = arg[i];
//         i++;
//     }
//     new[i] = '\0';
//     return (new);
// }