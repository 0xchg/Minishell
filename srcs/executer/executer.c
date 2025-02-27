/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:35:17 by mchingi           #+#    #+#             */
/*   Updated: 2025/02/27 16:35:03 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	clean_t_pipe(t_pipe *pipes, char	*str)
{
	free(pipes);
	error_message(str);
}

static int	pipe_flag(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	unamed_function(t_token *token, t_pipe *pip, t_type type)
{
	if (type == PIPE)
		execute_cmd_in_pipe(token, pip, pip->input_fd, pip->pipe_fd[1]);
	else
		execute_cmd_in_pipe(token, pip, pip->input_fd, STDOUT_FILENO);
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
		execute_redirections(token);
		if (is_builtin(token->type))
		{
			if (type == PIPE)
				dup3(pip->pipe_fd[1], STDOUT_FILENO);
			execute_builtins(shell, token);
			exit(0);
		}
		else
			unamed_function(token, pip, type);
	}
	if (pip->input_fd != 0)
		close(pip->input_fd);
	if (type == PIPE)
	{
		close(pip->pipe_fd[1]);
		pip->input_fd = pip->pipe_fd[0];
	}
}

int	executer(t_shell *shell, t_token *tokens)
{
	t_pipe	*pipes;
	t_token	*cmd_start;

	pipes = malloc(sizeof(t_pipe));
	if (!pipes)
		error_message("malloc");
	pipes->i = 0;
	pipes->input_fd = 0;
	pipes->flag = pipe_flag(tokens);
	pipes->ev = shell->ev;
	cmd_start = tokens;
	while (cmd_start)
	{
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
	free(pipes);
	return (0);
}
