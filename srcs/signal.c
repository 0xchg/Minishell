/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:32:01 by marcsilv          #+#    #+#             */
/*   Updated: 2025/03/20 11:24:44 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

extern volatile sig_atomic_t	g_sigint;

void	set_sigint(int *num, char write)
{	
	static int	*sig;

	if (!sig)
		sig = num;
	else if (write)
		*sig = 130;
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
