/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:47:02 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/07 15:24:14 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static char	*extract_command(char **input)
{
	char	*command;
	int		i;

	i = 0;
	while (**input && !ft_isspace(**input) && \
	!ft_strchr("|<>«»&*", **input) && **input != '\'' && **input != '\"')
	{
		i++;
		(*input)++;
	}
	command = ft_strndup((*input) - i, i);
	return (command);
}

char	*extract_variable(char **input)
{
	char	*variable;
	int		i;
	char	*temp;

	i = 0;
	(*input)++;
	while (**input && (ft_isalnum(**input) || **input == '_' || **input == '?'))
	{
		i++;
		(*input)++;
	}
	temp = ft_strndup((*input) - i, i);
	variable = safe_malloc(sizeof(char) * (i + 2));
	variable[0] = '$';
	ft_strncpy(variable + 1, temp, i);
	variable[i + 1] = '\0';
	free(temp);
	return (variable);
}

static char	**split_input(char *input)
{
	int		i;
	char	**array;

	i = 0;
	if (!validate_quote_number(input))
		return (NULL);
	array = safe_malloc(sizeof(char *) * (word_count(input) + 1));
	while (*input)
	{
		while (ft_isspace(*input) && *input)
			input++;
		if (*input == '\'' || *input == '\"')
			array[i++] = extract_quote(&input);
		else if (ft_strchr("|<>*&", *input))
			array[i++] = extract_operator(&input);
		else if (*input == '$')
			array[i++] = extract_variable(&input);
		else
			array[i++] = extract_command(&input);
	}
	array[i] = NULL;
	return (array);
}

void	parse(t_shell *shell)
{
	char	*temp;

	temp = ft_strtrim(shell->input, " ");
	shell->flag = true;
	shell->array = split_input(temp);
	if (!shell->array)
		shell->flag = false;
	if (shell->flag)
	{
		expand(&shell->array, shell->env, shell);
		shell->token = tokenize_array(shell->array);
		if (!shell->token)
			error_message("token");
		identify_tokens(shell->token, shell->path);
		token_sequence(shell->token);
	}
	// ft_free(&shell->input);
	ft_free(&temp);
}
