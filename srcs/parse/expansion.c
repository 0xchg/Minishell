/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:02 by welepy            #+#    #+#             */
/*   Updated: 2025/03/15 21:19:55 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static char	*get_env_value(t_env *env, char *name)
{
	t_env	*tmp;
	tmp = env;

	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void change_strings(char ***matrix, t_env *env)
{
	int	i;
	char  *value;
	i = 0;
	while ((*matrix)[i])
	{
		value = get_env_value(env, (*matrix)[i]);
		ft_free(&(*matrix)[i]);
		(*matrix)[i] = value ? ft_strdup(value) : ft_strdup("");
		i++;
	}
}
static void	get_exit_status(t_shell *shell, t_token **token)
{
	char  *str;

	str = ft_itoa(shell->exit_status);
	ft_free(&(*token)->value);
	(*token)->value = ft_strdup(str);
	printf("number: %s\n", str);
	ft_free(&str);
}

void expansion(t_token *tokens, t_env *env, t_shell *shell)
{
	t_token *current;
	char  *str;
	char **matrix;

	current = tokens;
	while (current)
	{
		if ((ft_strlen(current->value) >= 2 || current->next) && ft_strchr(current->value, '$') && current->type != SINGLE_QUOTE)
		{
			if (current->value[1] == '?')
				get_exit_status(shell, &current);
			else if (ft_strchr(current->value, '$'))
			{
				str = ft_strtrim(current->value, " \t\n");
				matrix = ft_split(str, '$');
				change_strings(&matrix, env);
				ft_free(&current->value);
				current->value = join_matrix(matrix_len(matrix), matrix, "");
				free_matrix(matrix);
				ft_free(&str);
			}
		}
		current = current->next;
	}
}
