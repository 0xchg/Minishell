/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:35:17 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/13 16:43:33 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	init_pipe(t_pipe *pipe, t_token *tokens, t_shell *shell)
{
	if (!pipe)
		error_message("malloc");
	pipe->i = 0;
	pipe->input_fd = 0;
	pipe->flag = pipe_flag(tokens, shell);
}

int	executer(t_shell *shell, t_token *tokens)
{
	t_pipe	*pipes;
	t_token	*cmd_start;

	pipes = malloc(sizeof(t_pipe));
	init_pipe(pipes, tokens, shell);
	cmd_start = tokens;
	while (cmd_start)
	{
		if ((cmd_start->type == PIPE || !cmd_start->next) && pipes->flag == 1)
		{
			pipe_executer(shell, tokens, pipes, cmd_start->type);
			tokens = cmd_start->next;
		}
		else if (!cmd_start->next && !pipes->flag)
			command_executer(shell, tokens);
		cmd_start = cmd_start->next;
	}
	if (here_doc_flag(tokens))
		unlink(".DOC_TMP");
	free(pipes);
	return (shell->exit_status);
}
