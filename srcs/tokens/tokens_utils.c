/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:15:54 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/07 10:57:13 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	is_command_util(char **paths, int *tab, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(paths[tab[0]], "/");
	free(paths[tab[0]]);
	paths[tab[0]] = ft_strjoin(tmp, value);
	free(tmp);
}

bool	is_command(char *value, char *path)
{
	char	**paths;
	char	*tmp;
	int		tab[2];

	tab[1] = 0;
	tab[0] = 0;
	paths = ft_split(path, ':');
	while (paths[tab[0]])
	{
		is_command_util(paths, tab, value);
		tab[0]++;
	}
	tab[0] = 0;
	while (paths[tab[0]])
	{
		if (access(paths[tab[0]], F_OK) == 0)
		{
			tab[1] = 1;
			break ;
		}
		tab[0]++;
	}
	free_matrix(paths);
	return (tab[1]);
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
