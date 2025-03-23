/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:05:20 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/23 16:55:34 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

// long	atol_error(char *str)
// {
// 	ft_putstr_fd(str, 2);
// 	return (-1);
// }

bool	ft_atol_util(const char *str)
{
	if (ft_strlen(str) > 20)
		return (true);
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (true);
	return (false);
}

long long	ft_atol(const char *str)
{
	long				signal;
	unsigned long long	number;

	number = 0;
	signal = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signal = -1;
		str++;
	}
	if (ft_atol_util(str))
		return (939552403);
	while (ft_isdigit(*str))
	{
		number = (number * 10) + (*str - 48);
		str++;
	}
	if ((signal == 1 && number > LONG_MAX)
		|| (signal == -1 && number > (unsigned long long)LONG_MAX + 1))
		return (939552403);
	return (number * signal);
}
