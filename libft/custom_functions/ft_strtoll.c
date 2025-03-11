/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy </var/spool/mail/welepy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:17:44 by welepy            #+#    #+#             */
/*   Updated: 2025/03/11 13:19:44 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long long int	ft_strtoll(char *line)
{
	long long int	rslt;
	long long int	*hexa;
	int			cmp;
	int			power;

	cmp = 0;
	power = 0;
	rslt = 0;
	hexa = (long long int*)malloc(sizeof(long long int) * ft_strlen(line));
	while (line[cmp])
	{
		if (line[cmp] >= 'A' && line[cmp] <= 'F')
			hexa[cmp] = line[cmp] + 10 - 'A';
		else if (line[cmp] >= '0' && line[cmp] <= '9')
			hexa[cmp] = line[cmp] - '0';
		cmp++;
	}
	while (--cmp >= 0)
	{
		rslt += hexa[cmp] * ft_pow(16, power);
		power++;
	}
	free(hexa);
	return (rslt);
}
