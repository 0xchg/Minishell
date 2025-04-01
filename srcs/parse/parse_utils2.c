/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:56:56 by mchingi           #+#    #+#             */
/*   Updated: 2025/04/01 18:33:49 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

/* Calculates total length needed for concatenated quoted strings */
static size_t calculate_total_length(const char *str, bool *has_valid_quotes)
{
	size_t total_len;
	const char *current = str;
	char quote;

	*has_valid_quotes = false;
	total_len = 0;
	while (*current && is_quote(*current))
	{
		quote = *current++;
		const char *chunk_start = current;
		while (*current && *current != quote)
			current++;
		if (*current != quote)
			break;
		total_len += current - chunk_start;
		current++; // Skip closing quote
		*has_valid_quotes = true;
	}
	
	return (total_len);
}

/* Copies all quoted chunks into destination buffer */
static void copy_quoted_chunks(char *dest, const char *str)
{
	char	quote;
	const char *current = str;
	size_t chunk_len;
	size_t i;

	i = 0;
	while (*current && is_quote(*current))
	{
		quote = *current++;
		const char *chunk_start = current;
		while (*current && *current != quote)
			current++;
		if (*current != quote)
			break;
		chunk_len = current - chunk_start;
		while (i < chunk_len)
			*dest++ = chunk_start[i++];
		current++; // Skip closing quote
	}
	*dest = '\0';
}

/* ---------------------- Main Function ---------------------- */

char *extract_quote(char **input)
{
	char *result;
	bool has_valid_quotes;
	size_t total_len;
	char quote;
	
	if (!input || !*input || !is_quote(**input))
		return NULL;
	total_len = calculate_total_length(*input, &has_valid_quotes);
	if (!has_valid_quotes || total_len == 0)
		return NULL;
	result = safe_malloc(total_len + 1);
	copy_quoted_chunks(result, *input);
	while (**input && is_quote(**input))
	{
		quote = *(*input)++;
		while (**input && **input != quote)
			(*input)++;
		if (**input == quote)
			(*input)++;
	}
	printf("%s\n", result);
	return result;
}

bool	check_surroundings

char	*extract_quote(char **input)
{

}

static bool	extract_operator_util(char **input)
{
	int	i;

	i = 0;
	while ((*input)[i] == '*' && (*input)[i])
		i++;
	if (i > 1)
	{
		ft_dprintf(2, "syntax error near unexpected token `*'\n");
		while (ft_strchr("*", **input) && **input)
			(*input)++;
		return (false);
	}
	else if (ft_strchr("|&*<>", **input) && **input)
	{
		ft_dprintf(2, "syntax error near unexpected token `%c'\n", **input);
		while (ft_strchr("|&*<>", **input) && **input)
			(*input)++;
		return (false);
	}
	return (true);
}

char	*extract_operator(char **input, t_shell *shell)
{
	char	*operator;
	char	temp_char;
	int		i;
	int		operator_size;

	temp_char = **input;
	operator_size = 0;
	i = 0;
	while ((**input == temp_char) && (operator_size < 2))
	{
		++operator_size;
		(*input)++;
	}
	if (!extract_operator_util(input))
		shell->flag = false;
	operator = safe_malloc(sizeof(char) * (operator_size + 1));
	while (i < operator_size)
		operator[i++] = temp_char;
	operator[i] = '\0';
	return (operator);
}

int	expand_flag(char *input, int i)
{
	if (input[i] == '\'')
		return (-1);
	return (1);
}

/*int	number_of_commands(t_token *tokens)
{
	int		number;
	t_token	*tmp;

	number = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == FULL_COMMAND || tmp->type == COMMAND
			|| is_builtin(tmp->type))
			number++;
		tmp = tmp->next;
	}
	return (number);
}*/
