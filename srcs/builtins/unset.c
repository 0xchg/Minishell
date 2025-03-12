/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:49:17 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/12 16:14:43 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

void	remove_env(t_env **head, const char *name)
{
	t_env	*current;
	t_env	*previous;

	current = *head;
	previous = NULL;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*head = current->next;
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_env *env, t_token *token, t_shell *shell, bool flag)
{
	t_token	*temp;

	temp = token;
	if (!flag)
		temp = temp->next;
	while (temp && temp->type == ARGUMENT)
	{
		remove_env(&env, temp->value);
		temp = temp->next;
	}
	shell->exit_status = 0;
}
