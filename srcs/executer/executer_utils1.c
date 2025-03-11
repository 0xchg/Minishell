/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:34:43 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/10 20:13:01 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static	bool	type_checker(t_type type)
{
	bool	flag;

	flag = false;
	if (type == COMMAND)
		flag = true;
	else if (type == FULL_COMMAND)
		flag = true;
	else if (type == OPTION)
		flag = true;
	else if (type == ARGUMENT)
		flag = true;
	else if (type == DOUBLE_QUOTE)
		flag = true;
	else if (type == SINGLE_QUOTE)
		flag = true;
	return (flag);
}

static int	elem_counter(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (type_checker(tmp->type))
			count++;
		else if (is_redirection(tmp->type))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		else
			break ;
		tmp = tmp->next;
	}
	return (count);
}

static char	**fill_args(t_token *token, int size)
{
	int		i;
	char	**args;

	i = 0;
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (token)
	{
		if (type_checker(token->type))
			args[i++] = ft_strdup((token->value));
		else if (is_redirection(token->type))
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		else
			break ;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

char	**tokenize_command(t_token *token)
{
	int		count;
	char	**args;

	count = elem_counter(token);
	args = fill_args(token, count);
	return (args);
}

int	pipe_flag(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
