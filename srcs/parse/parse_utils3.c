/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:52:15 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/11 19:18:50 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static char	*process_expansion(char *str, t_env *env);

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

void	expand_util(char ***matrix, int y, t_env *env)
{
	char *expanded;

	expanded = process_expansion((*matrix)[y], env);
	if (!expanded)
		return;
	free((*matrix)[y]);
	(*matrix)[y] = expanded;
}

void	expand(char ***matrix, t_env *env, t_shell *shell)
{
	int		y;
	char	*temp;

	y = -1;
	while ((*matrix)[++y])
	{
		if ((*matrix)[y][0] == '$')
		{
			if ((*matrix)[y][1] == '?')
			{
				temp = ft_itoa(shell->exit_status);
				free((*matrix)[y]);
				(*matrix)[y] = temp;
			}
			else
			{
				temp = get_env_value(env, &(*matrix)[y][1]);
				if (temp)
				{
					free((*matrix)[y]);
					(*matrix)[y] = ft_strdup(temp);
				}
			}
		}
		else if (ft_strchr((*matrix)[y], '$') && ((*matrix)[y][0] != '\''))
			expand_util(matrix, y, env);
	}
}

static char	*process_expansion_helper(t_env *env, char *result, char *temp)
{
	char	*value;
	char	*new_result;

	value = get_env_value(env, temp);
	if (!value)
		value = "";
	new_result = ft_strjoin_free(result, value);
	ft_free(&temp);
	return (new_result);
}

static char	*process_expansion(char *str, t_env *env)
{
	char	*matrix[4];

	if (!str)
		return (NULL);
	matrix[0] = ft_strdup("");
	if (!matrix[0])
		return (NULL);
	matrix[1] = ft_strchr(str, '$');
	while (matrix[1])
	{
		matrix[2] = matrix[1];
		if (matrix[2] > str)
		{
			matrix[3] = ft_substr(str, 0, matrix[2] - str);
			matrix[0] = ft_strjoin_free(matrix[0], matrix[3]);
			ft_free(&matrix[3]);
		}
		matrix[1]++;
		matrix[2] = matrix[1];
		while (*matrix[2] && (ft_isalnum(*matrix[2]) || *matrix[2] == '_'))
			matrix[2]++;
		matrix[3] = ft_substr(matrix[1], 0, matrix[2] - matrix[1]);
		matrix[0] = process_expansion_helper(env, matrix[0], matrix[3]);
		str = matrix[2];
		matrix[1] = ft_strchr(matrix[1], '$');
	}
	matrix[0] = ft_strjoin_free(matrix[0], str);
	return (matrix[0]);
}

