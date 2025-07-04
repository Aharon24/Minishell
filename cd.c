#include "minishell.h"


// void ft_cd_more_argument(char *home, char *old_pwd,char  *path)
// {
//     char *new_pwd;
//     char *pwd;

//     pwd = getenv("PWD");

//     pwd = ft_strjoin(pwd,"/");
//     new_pwd = ft_strjoin(pwd,path);
//     printf("%s",new_pwd);


    
// }

void ft_cd(char **argv)
{
    char *old_pwd;
    char *home;
   // int i;

    home = getenv("HOME");
    old_pwd = getenv("OLDPWD");

  //printf("%s",home);
    if(argv[2] == NULL)
    {
        if(argv[2] == NULL && home != NULL)
        {
            if(chdir(home) ==  0)
                printf("n%s\n",home);
        }
        else
            perror(home);
    }
    // while (argv[i])
    //     i++;
    // if (i > 2)
    // {
    //     perror("Too MANY Arguments");
    //     return ;
    // }
    // ft_cd_more_argument(home , old_pwd,argv[1]);

}
