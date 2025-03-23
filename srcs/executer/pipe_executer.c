/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:45:13 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/23 17:03:00 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	clean_t_pipe(t_pipe *pipes, char	*str)
{
	free(pipes);
	error_message(str);
}

void	execute_cmd_in_pipe(t_token *token, t_shell *shell, int in, int out)
{
	char	*path;
	char	**args;
	char	**env;

	if (!token)
		return ;
	env = env_to_matrix(shell->env);
	args = tokenize_command(token);
	execute_full_command(args, env, in, out);
	path = find_path(args[0], env);
	if (!path)
	{
		ft_dprintf(2, "%s: command not found\n", args[0]);
		shell->exit_status = 127;
		free_matrix(env);
		free_matrix(args);
		ft_free(&path);
		exit(shell->exit_status);
	}
	if (in != 0)
		ft_dup3(in, STDIN_FILENO);
	if (out != 1)
		ft_dup3(out, STDOUT_FILENO);
	if (execve(path, args, env) == -1)
		error_message("execve");
}

void	redirect_pipe(t_token *token, t_pipe *pip, t_type type, t_shell *shell)
{
	if (type == PIPE)
		execute_cmd_in_pipe(token, shell, pip->input_fd, pip->pipe_fd[1]);
	else
		execute_cmd_in_pipe(token, shell, pip->input_fd, STDOUT_FILENO);
}

static void	pipe_executer_util(t_token *token, t_shell *shell,
	t_type type, t_pipe *pip)
{
	if (type == PIPE)
		ft_dup3(pip->pipe_fd[1], STDOUT_FILENO);
	if (redirection_flag(token))
		redirect_builtins(shell, token);
	else
		execute_builtins(shell, token);
}

void	pipe_exec_helper(t_shell *shell, t_token *token, t_type type, t_pipe *pip)
{
	pipe_executer_util(token, shell, type, pip);
	exit(shell->exit_status);
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
			pipe_exec_helper(shell, token, type, pip);
		else
			redirect_pipe(token, pip, type, shell);
	}
	waitpid(pip->id, &shell->exit_status, 0);
	if (WIFEXITED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	if (pip->input_fd != 0)
		close(pip->input_fd);
	if (type == PIPE)
	{
		close(pip->pipe_fd[1]);
		pip->input_fd = pip->pipe_fd[0];
	}
}
