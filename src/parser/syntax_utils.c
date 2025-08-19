#include "../../include/minishell.h"

static int	contains_forbidden_chars(const char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (ft_strchr(FORBIDDEN_CHARS, str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe(t_token *tok, t_token *prev)
{
	if (!prev || prev->type == T_PIPE)
		return (print_error("Unexpected token '|'\n", 1));
	if (!tok->next)
		return (print_error("Unexpected end after '|'\n", 1));
	return (0);
}

int	check_redirection(t_token *tok)
{
	if (!tok->next || tok->next->type != T_WORD)
		return (print_error("Redirection missing target\n", 1));
	if (tok->type == T_HEREDOC && tok->next->str[0] == '\0')
		return (print_error("Heredoc missing delimiter\n", 1));
	return (0);
}

int	check_word(t_token *tok)
{
	if (tok->quote_type == -1)
		return (print_error("Unclosed quote\n", 1));
	if (tok->quote_type == 0 && contains_forbidden_chars(tok->str))
	{
		ft_printf("Syntax Error: Forbidden character in token '%s'\n", tok->str);
		return (1);
	}
	return (0);
}
