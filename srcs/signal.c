/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:32:01 by marcsilv          #+#    #+#             */
/*   Updated: 2025/03/09 15:08:20 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

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
		rl_redisplay();
	}
	ft_free(&cwd);
}
