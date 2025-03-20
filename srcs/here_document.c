/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:56:07 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/20 14:02:03 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

volatile sig_atomic_t	g_interrupted = 0;

void	setup_signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	cleanup_and_exit(int fd, char *delimeter)
{
	free(delimeter);
	close(fd);
	unlink(".DOC_TMP");
	exit(1);
}

void	read_input_and_write_to_file(int fd, char *delimeter)
{
	char	*input;

	while (1)
	{
		if (g_interrupted)
			cleanup_and_exit(fd, delimeter);
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
		free (input);
	}
}

void	here_doc(char *str)
{
	int		fd;
	char	*delimeter;

	delimeter = ft_strdup(str);
	fd = open(".DOC_TMP", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	setup_signal_handler();
	read_input_and_write_to_file(fd, delimeter);
	close(fd);
	free(delimeter);
}
