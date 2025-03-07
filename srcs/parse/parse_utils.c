/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:43:22 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/07 10:43:57 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

int	word_count_util(char *input, int count)
{
	char	quote;

	while (*input)
	{
		if (isspace(*input))
			input++;
		else
		{
			if (*input == '\'' || *input == '\"')
			{
				quote = *input++;
				while (*input && *input != quote)
					input++;
				if (*input)
					input++;
			}
			else
				while (*input && !isspace(*input) && \
				*input != '\'' && *input != '\"')
					input++;
			count++;
		}
	}
	return (count);
}

int	word_count(char *input)
{
	int	count;

	count = 0;
	count = word_count_util(input, count);
	return (count);
}

int	count_char(char *input, char c)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == c)
			count++;
		input++;
	}
	return (count);
}

static void	validate_quote_number_util(char *input, int *tab)
{
	if (*input == '\'')
	{
		tab[0]++;
		input++;
		while (*input && *input != '\'')
			input++;
		if (*input == '\'')
			tab[0]++;
	}
	else if (*input == '\"')
	{
		tab[1]++;
		input++;
		while (*input && *input != '\"')
			input++;
		if (*input == '\"')
			tab[1]++;
	}
}

bool	validate_quote_number(char *input)
{
	int	tab[2];

	tab[0] = 0;
	tab[1] = 0;
	while (*input)
	{
		validate_quote_number_util(input, tab);
		if (*input)
			input++;
	}
	if (tab[0] % 2 != 0 || tab[1] % 2 != 0)
	{
		ft_fprintf(2, "Error: can't parse unclosed quotes\n");
		return (false);
	}
	return (true);
}
