#include "../minishell.h"


void ft_cd_more_argument(char *old_pwd,char  *path)
{
    char *new_pwd;
    char *pwd;
    pwd = old_pwd;
    pwd = getenv("PWD");

    pwd = ft_strjoin(pwd,"/");
    new_pwd = ft_strjoin(pwd,path);
    chdir(new_pwd);
    //printf("%s",new_pwd);

}

void    ft_cd(char **argv)
{
    char    *old_pwd;
    char    *home;
    int     i;

    i = 0;
    home = getenv("HOME");
    old_pwd = getenv("OLDPWD");

  
    if (argv[1] == NULL)
    {
        if (argv[1] == NULL && home != NULL)
            chdir(home);
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
    ft_cd_more_argument(old_pwd,argv[1]);
}
