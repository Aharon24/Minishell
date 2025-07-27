#include "minishell.h"

void new_cmd_init(t_command *new_cmd)
{
    new_cmd->argv = NULL;
    new_cmd->pip = 0;
    new_cmd->redirects = NULL;
    new_cmd->next = NULL;
	new_cmd->syntax_error = 0;
}

int size_(t_token *tokens)
{
    int size = 0;
    while (tokens && tokens->type != TOKEN_PIPE)
    {
        if (tokens->type == TOKEN_WORD)
            size++;
        tokens = tokens->next;
    }
    return size;
}

t_command *allocate_new_command(t_token *tokens)
{
    int size = size_(tokens);
    t_command *new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return NULL;
    new_cmd_init(new_cmd);
    new_cmd->argv = malloc(sizeof(char *) * (size + 1));
    if (!new_cmd->argv)
    {
        free(new_cmd);
        return NULL;
    }
    return new_cmd;
}

int process_redirect(t_token **tokens, t_command *new_cmd, t_shell *shell)
{
    t_redirect *redir = malloc(sizeof(t_redirect));
    if (!redir)
        return -1;

    redir->type = (*tokens)->type;
    *tokens = (*tokens)->next;

    if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
    {
        redir->filename = NULL;
        redir->next = NULL;
        add_redirect(&new_cmd->redirects, redir);
        return 0;
    }

    redir->filename = remove_quotes_and_expand((*tokens)->value, shell->env);
    if (!redir->filename)
    {
        free(redir);
        return -1;
    }

    redir->next = NULL;
    add_redirect(&new_cmd->redirects, redir);
    *tokens = (*tokens)->next;
    return 0;
}


int fill_argv_and_redirects(t_token **tokens, t_command *new_cmd, t_shell *shell)
{
    int i = 0;
    while (*tokens && (*tokens)->type != TOKEN_PIPE)
    {
        if ((*tokens)->type == TOKEN_WORD)
        {
            new_cmd->argv[i] = remove_quotes_and_expand((*tokens)->value, shell->env);
            if (!new_cmd->argv[i])
                return -1;
            i++;
            *tokens = (*tokens)->next;
        }
        else if ((*tokens)->type == TOKEN_REDIRECT_IN
              || (*tokens)->type == TOKEN_HEREDOC
              || (*tokens)->type == TOKEN_REDIRECT_OUT
              || (*tokens)->type == TOKEN_REDIRECT_APPEND)
        {
            if (process_redirect(tokens, new_cmd, shell) == -1)
                return -1;
        }
        else
        {
            *tokens = (*tokens)->next;
        }
    }
    new_cmd->argv[i] = NULL;
    return 0;
}

t_command *split_cmd(t_token *tokens, t_shell *shell)
{
    t_command *cmd_head = NULL;
    t_command *new_cmd;

    while (tokens)
    {
        new_cmd = allocate_new_command(tokens);
        if (!new_cmd)
        {
            free_cmd(cmd_head);
            return NULL;
        }
        if (fill_argv_and_redirects(&tokens, new_cmd, shell) == -1)
        {
            free_command(new_cmd);
            free_cmd(cmd_head);
            return NULL;
        }
        if (tokens && tokens->type == TOKEN_PIPE)
        {
            new_cmd->pip = 1;
            tokens = tokens->next;
        }
        add_new_cmd(&cmd_head, new_cmd);
    }
    return cmd_head;
}
