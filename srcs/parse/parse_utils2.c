/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:56:56 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/30 16:38:16 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

char	*fill_quote(char **input, char quote, int i)
{
	char	*quote_string;
	char	*temp;

	temp = strndup((*input) - i, i);
	quote_string = safe_malloc(sizeof(char) * (i + 3));
	quote_string[0] = quote;
	strncpy(quote_string + 1, temp, i);
	quote_string[i + 1] = quote;
	quote_string[i + 2] = '\0';
	free(temp);
	return (quote_string);
}

char	*extract_quote(char **input)
{
	int		i;
	char	quote;
	char	*quote_string;

	i = 0;
	quote = **input;
	(*input)++;
	while (**input)
	{
		if (**input == quote)
		{
			if (*(*input) == quote)
				break ;
		}
		(*input)++;
		i++;
	}
	quote_string = fill_quote(input, quote, i);
	if (**input)
		(*input)++;
	return (quote_string);
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
