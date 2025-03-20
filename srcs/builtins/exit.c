/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:49:03 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/12 22:41:17 by welepy           ###   ########.fr       */
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
	if (string[0] == '-' || string[0] == '+')
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
	char	*arr[2];

	if (token->next)
	{
		arr[0] = ft_strtrim(token->next->value, " \n\t");
		errno = 0;
		if (arr[0])
			shell->exit_status = modulo((strtoll(arr[0], &arr[1], 10)));
		printf("exit\n");
		if (!all_nums(arr[0]) || all_spaces(token->next->value) || *arr[1]
			|| errno == ERANGE || int_overflow(strtoll(arr[0], &arr[1], 10)))
		{
			shell->exit_status = 2;
			ft_fprintf(2, "exit: %s numeric argument required\n", (arr[0]));
		}
		else if (token->next->next)
		{
			shell->exit_status = 1;
			ft_free(&arr[0]);
			return (ft_fprintf(2, "exit: too many arguments\n"));
		}
		ft_free(&arr[0]);
	}
	clean_or_exit(shell);
	exit(shell->exit_status);
}
