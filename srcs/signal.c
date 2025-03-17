/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:32:01 by marcsilv          #+#    #+#             */
/*   Updated: 2025/03/16 18:45:16 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

extern volatile sig_atomic_t	g_sigint;

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
		g_sigint = 130;
		rl_redisplay();
	}
	ft_free(&cwd);
}
