/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:36:50 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/12 16:21:50 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

void	redirect_input(t_token *token, t_shell *shell)
{
	int	fd;

	if (!token || !token->next)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token 'newline'\n");
		shell->exit_status = 2;
		exit(shell->exit_status);
	}
	fd = open(token->next->value, O_RDONLY);
	if (fd == -1)
	{
		perror(token->next->value);
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(t_token *token, t_shell *shell)
{
	int	fd;

	if (!token || !token->next)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token 'newline'\n");
		shell->exit_status = 2;
		exit(shell->exit_status);
	}
	fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(token->next->value);
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_output_append(t_token *token, t_shell *shell)
{
	int	fd;

	if (!token || !token->next)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token 'newline'\n");
		shell->exit_status = 2;
		exit(shell->exit_status);
	}
	fd = open(token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_here_doc(t_token *token, t_shell *shell)
{
	int	fd;

	if (!token || !token->next)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token 'newline'\n");
		shell->exit_status = 2;
		exit(shell->exit_status);
	}
	here_doc(token->next->value);
	fd = open(".DOC_TMP", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	execute_redirections(t_token *token, t_shell *shell)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == LESSER)
			redirect_input(tmp, shell);
		else if (tmp->type == GREATER)
			redirect_output(tmp, shell);
		else if (tmp->type == APPEND)
			redirect_output_append(tmp, shell);
		else if (tmp->type == HERE_DOC)
			redirect_here_doc(tmp, shell);
		tmp = tmp->next;
	}
}
