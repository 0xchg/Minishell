/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:53:06 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/06 14:00:11 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

int	builtins_type(char *value)
{
	if (ft_strcmp(value, "echo") == 0)
		return (1);
	else if (ft_strcmp(value, "cd") == 0)
		return (1);
	else if (ft_strcmp(value, "pwd") == 0)
		return (1);
	else if (ft_strcmp(value, "env") == 0)
		return (1);
	else if (ft_strcmp(value, "export") == 0)
		return (1);
	else if (ft_strcmp(value, "unset") == 0)
		return (1);
	else if (ft_strcmp(value, "exit") == 0)
		return (1);
	return (0);
}

t_type	find_type(char *value)
{
	if (!ft_strcmp(value, ">"))
		return (GREATER);
	else if (!ft_strcmp(value, "<"))
		return (LESSER);
	else if (!ft_strcmp(value, ">>"))
		return (APPEND);
	else if (!ft_strcmp(value, "<<"))
		return (HERE_DOC);
	else if (!ft_strcmp(value, "|"))
		return (PIPE);
	else if (builtins_type(value))
		return (BUILTINS);
	else if (value[0] == '\'')
		return (SINGLE_QUOTE);
	else if (value[0] == '\"')
		return (DOUBLE_QUOTE);
	else if (value[0] == '-')
		return (OPTION);
	else
		return (IDENTIFIER);
}

t_token	*tokenize_array(char **array)
{
	int		i;
	t_token	*new;
	t_token	*token;

	i = 0;
	token = NULL;
	while (array[i])
	{
		new = new_token(array[i], find_type(array[i]));
		ft_lstadd_back((t_list **)&token, (t_list *)new);
		i++;
	}
	return (token);
}

void	identify_tokens(t_token *tokens, char *path)
{
	t_token	*head;

	head = tokens;
	while (head)
	{
		if (head->type == IDENTIFIER)
		{
			if (is_command(head->value, path))
				head->type = COMMAND;
			else if (access(head->value, F_OK) == 0)
				head->type = FULL_COMMAND;
			else
				head->type = ARGUMENT;
		}
		head = head->next;
	}
}
