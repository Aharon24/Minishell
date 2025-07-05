#include "../minishell.h"


void ft_cd_more_argument(char  *path, t_shell *shell)
{
    int check;
    char *new_pwd1;
    char *new_pwd2;
    check = 0;

    
    new_pwd1 = ft_strjoin("/",path);
    new_pwd2 = ft_strjoin(new_pwd1,);


    /// .. 
}

void    ft_cd(char **argv, t_shell *shell)
{
    char    *old_pwd;
    char    *home;
    int     i;

    i = 0;
    home = ft_faind_in_env(shell->env,"HOME");
    if (home)
        shell->home = home;
    if (argv[1] == NULL)
    {
        if (argv[1] == NULL && home != NULL)
        {
            chdir(home);
            return ;
        }
        else
            perror(home);
    }
    while (argv[i])
        i++;
    if (i > 2)
    {
        perror("Too MANY Arguments");
        return ;
    }
    ft_cd_more_argument(argv[1],shell);
}
