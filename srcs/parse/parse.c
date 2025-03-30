/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:47:02 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/30 15:50:26 by marcsilv         ###   ########.fr       */
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
	if (!command)
		return (NULL);
	return (command);
}

static char	*extract_variable(char **input)
{
	char	*variable;
	int		i;
	char	*temp;

	i = 0;
	(*input)++;
	while (**input && (!ft_isspace(**input) && **input != '<'
	&& **input != '>' && **input != '|' && **input != '*' && **input != '&'))
	{
		i++;
		(*input)++;
	}
	temp = ft_strndup((*input) - i, i);
		if (!temp)
			return (NULL);
	variable = safe_malloc(sizeof(char) * (i + 2));
	variable[0] = '$';
	ft_strncpy(variable + 1, temp, i);
	variable[i + 1] = '\0';
	ft_free(&temp);
	return (variable);
}

bool	check_matrix_at_index(char **matrix, int i)
{
	if (!matrix[i])
	{
		free_matrix(matrix);
		return (false);
	}
	return (true);
}

static char	**split_input(char *input, t_shell *shell)
{
	int		i;
	char	**array;

	i = 0;
	array = safe_malloc(sizeof(char *) * ((size_t)word_count(input) + 1));
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input && (*input == '\'' || *input == '\"'))
			array[i++] = extract_quote(&input);
		else if (*input && ft_strchr("|<>*&", *input))
			array[i++] = extract_operator(&input, shell);
		else if (*input && (*input == '$'))
			array[i++] = extract_variable(&input);
		else
			array[i++] = extract_command(&input);
		if (i > 0 && !check_matrix_at_index(array, i - 1))
    	    return (NULL);
	}
	array[i] = NULL;
	return (array);
}

static void	error_quote(t_shell *shell)
{
	if (!validate_quote_number(shell->input))
	{
		ft_dprintf(2, "Error: can't parse unclosed quotes\n");
		shell->flag = false;
	}
}

void	parse(t_shell *shell)
{
	char	*temp;
	char	*expanded_temp;

	temp = ft_strtrim(shell->input, " ");
	shell->flag = true;
	error_quote(shell);
	expanded_temp = expand(temp, shell->env, shell->exit_status);
	ft_free(&temp);
	temp = expanded_temp;
	shell->flag = true;
	error_quote(shell);
	shell->array = split_input(temp, shell);
	if (!shell->flag)
		free_matrix(shell->array);

	if (shell->flag)
	{
		shell->token = tokenize_array(shell->array);
		identify_tokens(shell->token);
		token_sequence(shell->token);
	}
	ft_free(&temp);
}
