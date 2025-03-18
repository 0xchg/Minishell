/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:47:02 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/18 22:29:08 by welepy           ###   ########.fr       */
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

static char	**split_input(char *input, t_shell *shell)
{
	int		i;
	char	**array;

	i = 0;
	if (!validate_quote_number(input))
	{
		ft_fprintf(2, "Error: can't parse unclosed quotes\n");
		return (NULL);
	}
	array = safe_malloc(sizeof(char *) * (word_count(input) + 1));
	while (*input)
	{
		while (ft_isspace(*input) && *input)
			input++;
		if (*input == '\'' || *input == '\"')
			array[i++] = extract_quote(&input);
		else if (ft_strchr("|<>*&", *input))
			array[i++] = extract_operator(&input, shell);
		else if (*input == '$')
			array[i++] = extract_variable(&input);
		else
			array[i++] = extract_command(&input);
	}
	array[i] = NULL;
	return (array);
}

void parse(t_shell *shell)
{
	char *temp;
	char *expanded_temp;

	temp = ft_strtrim(shell->input, " ");
	expanded_temp = expand(temp, shell->env, shell->exit_status);
	free(temp);
	temp = expanded_temp;
	shell->flag = true;
	shell->array = split_input(temp, shell);
	if (!shell->flag)
		free_matrix(shell->array);
	if (!shell->array)
		shell->flag = false;
	if (shell->flag)
	{
		shell->token = tokenize_array(shell->array);
		if (!shell->token)
			error_message("token");
		identify_tokens(shell->token, shell->path);
		token_sequence(shell->token);
	}
	ft_free(&temp);
}
