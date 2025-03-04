/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:56:07 by mchingi           #+#    #+#             */
/*   Updated: 2025/02/27 11:50:51 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

void	here_doc(char *str)
{
	int		fd;
	char	*input;
	char	*delimeter;

	delimeter = strdup(str);
	fd = open(".DOC_TMP", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		input = readline("> ");
		if (!input || strcmp(input, delimeter) == 0)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		write(fd, input, strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(delimeter);
}
