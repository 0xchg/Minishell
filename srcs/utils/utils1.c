/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:59:50 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/23 15:04:48 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

bool	is_redirection(t_type type)
{
	return (type == LESSER || type == GREATER \
		|| type == HERE_DOC || type == APPEND);
}

bool	is_argument(t_type type)
{
	return (type == ARGUMENT || type == DOUBLE_QUOTE || type == SINGLE_QUOTE);
}

bool	is_option(t_type type)
{
	return (type == OPTION);
}

void	error_message(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_dup3(int fd, int fd2)
{
	dup2(fd, fd2);
	close(fd);
}
