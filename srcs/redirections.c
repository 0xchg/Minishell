/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:36:50 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/05 10:06:17 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

void	redirect_input(t_token *token)
{
	int	fd;

	if (!token || !token->next)
		return ;
	fd = open(token->next->value, O_RDONLY);
	if (fd == -1)
	{
		perror(token->next->value);
		exit(127);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(t_token *token)
{
	int	fd;

	if (!token || !token->next)
		return ;
	fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(token->next->value);
		exit(127);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_output_append(t_token *token)
{
	int	fd;

	if (!token || !token->next)
		return ;
	fd = open(token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(127);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_here_doc(t_token *token)
{
	int	fd;

	if (!token || !token->next)
		return ;
	here_doc(token->next->value);
	fd = open(".DOC_TMP", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(127);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	execute_redirections(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == LESSER)
			redirect_input(tmp);
		else if (tmp->type == GREATER)
			redirect_output(tmp);
		else if (tmp->type == APPEND)
			redirect_output_append(tmp);
		else if (tmp->type == HERE_DOC)
			redirect_here_doc(tmp);
		tmp = tmp->next;
	}
}
