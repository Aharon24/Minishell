#include "../minishell.h"


void ft_cd_more_argument(char *old_pwd,char  *path, t_shell *shell)
{
    char *s_pwd;
    char *new_pwd;
    int check;
    if(!shell->pwd)
        shell->pwd = ft_faind_in_env(shell->env,"PWD");
    s_pwd = ft_strjoin(shell->pwd,"/");
    new_pwd = ft_strjoin(s_pwd,path);
    printf(" new %s\n",new_pwd);
    if(ft_strncmp("..",path,2) == 0)
    {
        check = chdir(path);
        return ;
    }
    
    if((check = chdir(new_pwd)) == 0)
    {
        chdir(new_pwd);
        shell->pwd = new_pwd;
    }
    if(check < 0)
        perror("Not walid path");
    //printf("%s",new_pwd);
    /*
        -
        ..

    */
    printf(" lod %s path %s \n ",old_pwd,path);
}

void    ft_cd(char **argv, t_shell *shell)
{
    char    *old_pwd;
    char    *home;
    int     i;

    i = 0;
    home = getenv("HOME");
    if(home)
        shell->home = home;
    old_pwd = getenv("OLDPWD");

  
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
    ft_cd_more_argument(old_pwd,argv[1],shell);
}
