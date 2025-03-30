/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:45:43 by marcsilv          #+#    #+#             */
/*   Updated: 2025/03/30 17:46:56 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

void	error_quote(t_shell *shell)
{
	if (!validate_quote_number(shell->input))
	{
		ft_dprintf(2, "Error: can't parse unclosed quotes\n");
		shell->flag = false;
	}
}

bool	command_quote(char *str)
{
	int		i;
	char	quote;

	if (!str || !*str)
		return (false);
	if (*str != '\'' && *str != '\"')
		return (false);
	
	quote = *str;
	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (true);
		i++;
	}
	return (false);
}