/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:48:53 by mchingi           #+#    #+#             */
/*   Updated: 2025/02/26 03:37:29 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minihell.h"

static bool	is_valid_option(char *value)
{
	int	i;

	if (value[0] != '-')
		return (false);
	if (value[1] == '\0')
		return (false);
	i = 1;
	while (value[i])
	{
		if (value[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	check_input(char *input)
{
	char *single_q;
	char *double_q;

	single_q = ft_strchr(input, '\'');
	double_q = ft_strchr(input, '\"');
	if (single_q)
	{
		single_q--;
		if (!ft_isspace(*single_q))
			return (true);
	}
	else if (double_q)
	{
		double_q--;
		if (!ft_isspace(*double_q))
			return (true);
	}
	return false;
}

static bool	echo_aux(t_token *token, bool *option, char *input)
{
	t_token	*temp;
	t_token	*temp2;
	bool	is_first_argument = true;
	bool	previous_char = check_input(input);
	temp = token->next;
	while (temp && temp->type == OPTION && is_valid_option(remove_quotes(temp->value)))
	{
		*option = true;
		temp = temp->next;
	}
	temp2 = temp;
	while (temp2 && temp2->type == OPTION)
	{
		temp2->type = ARGUMENT;
		temp2 = temp2->next;
	}
	while (temp && (temp->type == ARGUMENT || temp->type == SINGLE_QUOTE || temp->type == DOUBLE_QUOTE || temp->type == OPTION))
	{
		if (!is_first_argument && !previous_char)
			printf(" ");
		is_first_argument = false;
		printf("%s", remove_quotes(temp->value));

		temp = temp->next;
	}
	return (*option);
}

void	ft_echo(t_token *token, t_shell *shell)
{
	bool	option = false;

	if (!token)
	{
		write(1, "\n", 1);
		return ;
	}
	option = echo_aux(token, &option, remove_quotes(shell->input));
	if (!option)
		printf("\n");
}