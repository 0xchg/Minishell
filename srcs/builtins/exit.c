/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:49:03 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/02 17:54:35 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minihell.h"

// Claramente falta muito

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

void	clean_or_exit(t_shell *shell)
{
	free_env(shell->env);
	ft_free(&shell->input);
	free_tokens(shell->token);
	free_matrix(shell->array);
	ft_free(&shell->path);
	rl_clear_history();
}

void	ft_exit(t_shell *shell)
{
	printf("\nfrom builtins\n");
	clean_or_exit(shell);
	free(shell);
	exit(EXIT_SUCCESS);
}