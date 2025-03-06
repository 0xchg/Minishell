/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:00:34 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/06 14:25:22 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

bool	is_lesser(t_type token)
{
	return (token == LESSER);
}

bool	is_greater(t_type token)
{
	return (token == GREATER);
}

bool	is_append(t_type token)
{
	return (token == APPEND);
}

bool	is_builtin_or_command(t_type type)
{
	return (type == COMMAND || type == BUILTINS || type == FULL_COMMAND);
}

bool	is_builtin(t_type type)
{
	return (type == BUILTINS);
}
