#include "minishell.h"

void    split_cmd(t_command *cmd, t_token *tokens)
{
    int i;
    t_command *new_cmd;
    int size;

    while (tokens)
    {
        size = count_word(tokens);
        if (tokens->type != 1)
        {
            cmd->argv = malloc(sizeof(char) * (size + 1));
            i = 0;
            while (tokens->type != 1 && tokens)
            {
                cmd->argv[i] = tokens->value;
                i++;
                tokens = tokens->next;
            }
            cmd->argv[i] = '\0';
        }
        else
        {
            new_cmd = malloc(sizeof(t_command));
            if ()
        }
    }
}