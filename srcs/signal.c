/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:32:01 by marcsilv          #+#    #+#             */
/*   Updated: 2025/03/22 15:41:23 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

extern volatile sig_atomic_t	g_sigint;
extern volatile sig_atomic_t	g_interrupted;

void	set_sigint(int *num, char write)
{
	static int	*sig;

	if (!sig)
		sig = num;
	else if (write)
		*sig = 130;
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_interrupted = 1;
}

void	signal_handler(int sig)
{
	char	*cwd;

	cwd = safe_malloc(PATH_MAX);
	getcwd(cwd, PATH_MAX);
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("┌[%s] - [%s]\n", getenv("USER"), cwd);
		set_sigint(NULL, 1);
		rl_redisplay();
	}
	ft_free(&cwd);
}

void	process_signal_handler(int sig)
{
	(void) sig;
	printf("\n");
}

