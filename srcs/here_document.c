/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:56:07 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/06 15:34:56 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

void	here_doc(char *str)
{
	int		fd;
	char	*input;
	char	*delimeter;

	delimeter = ft_strdup(str);
	fd = open(".DOC_TMP", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, delimeter) == 0)
		{
			free(input);
			break ;
		}
		if (*input)
			add_history(input);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(delimeter);
}
