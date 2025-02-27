/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:20:55 by mchingi           #+#    #+#             */
/*   Updated: 2025/02/27 16:13:05 by mchingi          ###   ########.fr       */
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

void	execute_command(t_token *token, char **env)
{
	char	*path;
	char	**args;

	if (!token)
		return ;
	args = tokenize_command(token);
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

	execute_redirections(tokens);
	if (is_builtin(tokens->type))
		execute_builtins(shell, tokens);
	else
	{
		id = fork();
		if (id == -1)
			error_message("fork");
		if (id == 0)
			execute_command(tokens, shell->ev);
	}
}
