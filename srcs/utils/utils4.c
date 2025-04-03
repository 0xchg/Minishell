/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:57:46 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/28 10:00:16 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

t_env	*last_env(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*t;

	if (*env)
	{
		t = last_env(*env);
		t->next = new;
	}
	else
		*env = new;
}
