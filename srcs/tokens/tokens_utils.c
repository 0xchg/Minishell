/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:15:54 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/06 14:24:21 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

bool	is_command(char *value, char *path)
{
	char	**paths;
	int		i;
	char	*tmp;
	bool	found;

	found = false;
	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, value);
		free(tmp);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			found = true;
			break ;
		}
		i++;
	}
	free_matrix(paths);
	return (found);
}

t_token	*new_token(char *value, t_type type)
{
	t_token	*new_token;

	new_token = safe_malloc(sizeof(t_token));
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	token_sequence(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	while (head)
	{
		if (is_builtin_or_command(head->type) && head->next \
			&& is_builtin_or_command(head->next->type))
		{
			while (head->next && (is_builtin_or_command(head->next->type)))
			{
				head->next->type = ARGUMENT;
				head = head->next;
			}
		}
		if (is_redirection(head->type) && head->next \
			&& is_builtin_or_command(head->next->type))
			head->next->type = ARGUMENT;
		head = head->next;
	}
}

/*char	*token_kind_string(t_type type)
{
	if (type == GREATER)
		return ("GREATER");
	else if (type == LESSER)
		return ("LESSER");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HERE_DOC)
		return ("Here-doc");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == COMMAND)
		return ("COMMAND");
	else if (type == ARGUMENT)
		return ("ARGUMENT");
	else if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (type == DOUBLE_QUOTE)
		return ("DOUBLE QUOTE");
	else if (type == BUILTINS)
		return ("Builtins");
	else if (type == OPTION)
		return ("OPTION");
	else if (type == FULL_COMMAND)
		return ("FULL_COMMAND");
	else if (type == IDENTIFIER)
		return ("IDENTIFIER");
	else
		return ("UNKNOWN");
}*/
