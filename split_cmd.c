#include "minishell.h"

void new_cmd_init(t_command *new_cmd)
{
    new_cmd->argc = 0;
    new_cmd->argv = NULL;
    new_cmd->next = NULL;
}

int size_(t_token *tokens)
{
    int size = 0;
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        size++;
        tokens = tokens->next;
    }
    return size;
}

void add_new_cmd(t_command **cmd_head, t_command *new_cmd)
{
    t_command *last;

    if (!(*cmd_head))
    {
        *cmd_head = new_cmd;
    }
    else
    {
        last = *cmd_head;
        while (last->next)
            last = last->next;
        last->next = new_cmd;
    }
}

t_command *split_cmd(t_token *tokens)
{
    t_command *cmd_head;
    t_command *new_cmd;
    int i;
    int size;

    cmd_head = NULL;
    while (tokens)
    {
        new_cmd = malloc(sizeof(t_command));
        if (!new_cmd)
            return NULL;
        new_cmd_init(new_cmd);
        size = size_(tokens);
        new_cmd->argv = malloc(sizeof(char *) * (size + 1));
        if (!new_cmd->argv)
            return NULL;
        i = 0;
        while (tokens && tokens->type != TOKEN_PIPE)
        {
            new_cmd->argv[i++] = tokens->value;
            tokens = tokens->next;
        }
        new_cmd->argv[i] = NULL;
        new_cmd->argc = i;
        add_new_cmd(&cmd_head, new_cmd);
        if (tokens && tokens->type == TOKEN_PIPE)
            tokens = tokens->next;
    }
    return cmd_head;
}
