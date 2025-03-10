/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:49:03 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/10 21:07:11 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	free_env(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		ft_free(&head->name);
		ft_free(&head->value);
		if (head)
		{
			free(head);
			head = NULL;
		}
		head = tmp;
	}
}

static bool	all_nums(char *string)
{
	int	i;

	i = -1;
	if (string[0] == '-')
	{
		i = 0;
		if (string[1] && !ft_isdigit(string[1]))
			return (false);
	}
	while (string[++i])
	{
		if (!ft_isdigit(string[i]))
			return (false);
	}
	return (true);
}

void	clean_or_exit(t_shell *shell)
{
	free_env(shell->env);
	ft_free(&shell->input);
	free_tokens(shell->token);
	free_matrix(shell->array);
	ft_free(&shell->path);
	rl_clear_history();
}

static int	modulo(long long int exit_status)
{
	if (exit_status >= 0 && exit_status <= 255)
		return (exit_status);
	return (exit_status % 256);
}

void	ft_exit(t_shell *shell, t_token *token)
{
	char	*trimmed;
	if(token->next)
	{
		trimmed = ft_strtrim(token->next->value, " \n\t");
		if (trimmed)
			shell->exit_status = modulo(ft_atoi(trimmed));
		if (!all_nums(trimmed))
		{
			shell->exit_status = 2;
			ft_fprintf(2, "exit: %s numeric argument required\n",
				 (trimmed));
		}
		else if (token->next->next)
		{
			shell->exit_status = 1;
			ft_fprintf(2, "exit: too many arguments\n");
			ft_free(&trimmed);
			return ;
		}
		ft_free(&trimmed);
	}
	clean_or_exit(shell);
	exit(shell->exit_status);
}
