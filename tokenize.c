#include "minishell.h"

int	lex_word(char *line, t_token **tokens)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<' && line[i] != '>')
		i++;
	word = ft_strndup(&line[0], i);
	add_token(tokens, word, TOKEN_WORD);
	return (i);
}

int	lex_redir(char *line, t_token **tokens)
{
	if (line[0] == '>' && line[1] == '>')
	{
		add_token(tokens, ft_strdup(">>"), TOKEN_REDIRECT_APPEND);
		return (2);
	}
	else if (line[0] == '<' && line[1] == '<')
	{
		add_token(tokens, strdup("<<"), TOKEN_HEREDOC);
		return (2);
	}
	else
	{
		if (line[0] == '>')
			add_token(tokens, ft_strdup(">"), TOKEN_REDIRECT_OUT);
		else
			add_token(tokens, ft_strdup("<"), TOKEN_REDIRECT_IN);
		return (1);
	}
}

int	lex_pipe(t_token **tokens)
{
	add_token(tokens, ft_strdup("|"), TOKEN_PIPE);
	return (1);
}

int	lexer(char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|')
			i += lex_pipe(tokens);
		else if (line[i] == '>' || line[i] == '<')
			i += lex_redir(&line[i], tokens);
		else
			i += lex_word(&line[i], tokens);
	}
	return (0);
}

int	tokenize(t_shell *shell)
{
	if (lexer(shell->line, &(shell->tokens)) == -1)
		return (-1);
	return (0);
}
