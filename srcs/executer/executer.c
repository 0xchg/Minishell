/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:35:17 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/06 15:42:02 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	clean_t_pipe(t_pipe *pipes, char	*str)
{
	free(pipes);
	error_message(str);
}

void	child_pipe(t_token *token, t_pipe *pip, t_type type, t_shell *shell)
{
	if (type == PIPE)
		execute_cmd_in_pipe(token, shell, pip->input_fd, pip->pipe_fd[1]);
	else
		execute_cmd_in_pipe(token, shell, pip->input_fd, STDOUT_FILENO);
}

void	pipe_executer(t_shell *shell, t_token *token, t_pipe *pip, t_type type)
{
	if (pipe(pip->pipe_fd) == -1)
		clean_t_pipe(pip, "pipe");
	pip->id = fork();
	if (pip->id == -1)
		clean_t_pipe(pip, "fork");
	if (pip->id == 0)
	{
		execute_redirections(token, shell);
		if (is_builtin(token->type))
		{
			if (type == PIPE)
				dup3(pip->pipe_fd[1], STDOUT_FILENO);
			execute_builtins(shell, token);
			exit(0);
		}
		else
			child_pipe(token, pip, type, shell);
	}
	if (pip->input_fd != 0)
		close(pip->input_fd);
	if (type == PIPE)
	{
		close(pip->pipe_fd[1]);
		pip->input_fd = pip->pipe_fd[0];
	}
}

void	init_pipe(t_pipe *pipe, t_shell *shell, t_token *tokens)
{
	if (!pipe)
		error_message("malloc");
	pipe->i = 0;
	pipe->input_fd = 0;
	pipe->flag = pipe_flag(tokens);
	pipe->ev = env_to_matrix(shell->env);
}

int	executer(t_shell *shell, t_token *tokens)
{
	t_pipe	*pipes;
	t_token	*cmd_start;

	pipes = malloc(sizeof(t_pipe));
	init_pipe(pipes, shell, tokens);
	cmd_start = tokens;
	while (cmd_start)
	{
		shell->exit_status = 0;
		if ((cmd_start->type == PIPE || !cmd_start->next) && pipes->flag)
		{
			pipe_executer(shell, tokens, pipes, cmd_start->type);
			tokens = cmd_start->next;
		}
		else if (!cmd_start->next && !pipes->flag)
			command_executer(shell, tokens);
		cmd_start = cmd_start->next;
	}
	while (wait(NULL) > 0);
	if (here_doc_flag(tokens))
		unlink(".DOC_TMP");
	free_matrix(pipes->ev);
	free(pipes);
	return (shell->exit_status);
}
