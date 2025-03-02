/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:20:55 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/02 18:51:38 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

void	execute_builtins(t_shell *shell, t_token *token)
{
	if (strcmp(token->value, "echo") == 0)
		ft_echo(token, shell);
	else if (strcmp(token->value, "cd") == 0)
		ft_cd(token);
	else if (strcmp(token->value, "pwd") == 0)
		ft_pwd(token);
	else if (strcmp(token->value, "env") == 0)
		ft_env(shell->env, token);
	else if (strcmp(token->value, "export") == 0)
		ft_export(shell->env, token);
	else if (strcmp(token->value, "unset") == 0)
		ft_unset(shell->env, token);
	else if (strcmp(token->value, "exit") == 0)
		ft_exit(shell);
	printf("\nfrom builtins\n");
}

void	execute_full_command(char **args, char **env, int in, int out)
{
	char	*path;

	if (access(args[0], F_OK) == 0)
	{
		path = ft_strdup(args[0]);
		args[0] = ft_strtrim(args[0], "/bin/");
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		if (execve(path, args, env) == -1)
			error_message("execve");
	}
}

void	execute_command(t_token *token, char **env)
{
	char	*path;
	char	**args;

	if (!token)
		return ;
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
		printf("%s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(path, args, env) == -1)
		error_message("execve");
}

void	execute_cmd_in_pipe(t_token *token, t_pipe *pipes, int in, int out)
{
	char	*path;
	char	**args;

	if (!token)
		return ;
	args = tokenize_command(token);
	execute_full_command(args, pipes->ev, in, out);
	path = find_path(args[0], pipes->ev);
	if (!path)
	{
		printf("%s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}
	if (in != 0)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	if (execve(path, args, pipes->ev) == -1)
		error_message("execve");
}

void	command_executer(t_shell *shell, t_token *tokens)
{
	pid_t	id;

	if (is_builtin(tokens->type))
		{
			execute_redirections(tokens);
			execute_builtins(shell, tokens);
		}
	else
	{
		id = fork();
		if (id == -1)
			error_message("fork");
		if (id == 0)
		{
			execute_redirections(tokens);
			execute_command(tokens, shell->ev);
		}
	}
}
