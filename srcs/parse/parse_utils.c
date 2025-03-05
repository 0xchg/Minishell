/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:43:22 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/03 14:49:55 by marcsilv         ###   ########.fr       */
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

bool	validate_quote_number(char *input)
{
	int	single_quote_count;
    int	double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
    while (*input)
    {
        if (*input == '\'')
        {
            single_quote_count++;
            input++;
            while (*input && *input != '\'')
                input++;
            if (*input == '\'')
                single_quote_count++;
        }
        else if (*input == '\"')
        {
            double_quote_count++;
            input++;
            while (*input && *input != '\"')
                input++;
            if (*input == '\"')
                double_quote_count++;
        }
        if (*input)
            input++;
    }
    if (single_quote_count % 2 != 0 || double_quote_count % 2 != 0)
        return (false);
    return (true);
}
