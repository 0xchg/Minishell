/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:20:55 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/07 11:16:01 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

void	execute_builtins(t_shell *shell, t_token *token)
{
	if (ft_strcmp(token->value, "echo") == 0)
		ft_echo(token, shell);
	else if (ft_strcmp(token->value, "cd") == 0)
		ft_cd(token, shell);
	else if (ft_strcmp(token->value, "pwd") == 0)
		ft_pwd(token, shell);
	else if (ft_strcmp(token->value, "env") == 0)
		ft_env(shell->env, token, shell, false);
	else if (ft_strcmp(token->value, "export") == 0)
		ft_export(shell->env, token, shell);
	else if (ft_strcmp(token->value, "unset") == 0)
		ft_unset(shell->env, token, shell);
	else if (ft_strcmp(token->value, "exit") == 0)
		ft_exit(shell);
}

void	execute_full_command(char **args, char **env, int in, int out)
{
	char	*path;

	if (access(args[0], F_OK) == 0)
	{
		path = ft_strdup(args[0]);
		args[0] = ft_strtrim(args[0], "/bin/");
		if (in != 0)
			dup3(in, STDIN_FILENO);
		if (out != 1)
			dup3(out, STDOUT_FILENO);
		if (execve(path, args, env) == -1)
			error_message("execve");
	}
}

void	execute_command(t_token *token, t_shell *shell)
{
	char	*path;
	char	**args;
	char	**env;

	if (!token)
		return ;
	env = env_to_matrix(shell->env);
	args = tokenize_command(token);
	if (access(args[0], F_OK) == 0)
	{
		path = ft_strdup(args[0]);
		args[0] = ft_strtrim(args[0], "/bin/");
		if (execve(path, args, env) == -1)
			error_message("execve");
	}
	path = find_path(args[0], env);
	if (!path)
	{
		ft_fprintf(2, "%s: command not found\n", args[0]);
		shell->exit_status = 127;
		free_matrix(env);
		exit(EXIT_FAILURE);
	}
	if (execve(path, args, env) == -1)
		error_message("execve");
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
		ft_fprintf(2, "%s: command not found\n", args[0]);
		shell->exit_status = 127;
		free_matrix(env);
		exit(EXIT_FAILURE);
	}
	if (in != 0)
		dup3(in, STDIN_FILENO);
	if (out != 1)
		dup3(out, STDOUT_FILENO);
	if (execve(path, args, env) == -1)
		error_message("execve");
}

void	command_executer(t_shell *shell, t_token *tokens)
{
	pid_t	id;

	if (is_builtin(tokens->type))
	{
		execute_redirections(tokens, shell);
		execute_builtins(shell, tokens);
	}
	else
	{
		id = fork();
		if (id == -1)
			error_message("fork");
		if (id == 0)
		{
			execute_redirections(tokens, shell);
			execute_command(tokens, shell);
		}
	}
}
