/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:52:15 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/13 16:29:05 by mchingi          ###   ########.fr       */
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

void	expand_util(char ***matrix, int y, char *arr, t_env *env)
{
	arr = process_expansion((*matrix)[y], env);
	free((*matrix)[y]);
	(*matrix)[y] = arr;
}

void	expand(char ***matrix, t_env *env, t_shell *shell)
{
	int		y;
	char	*arr[2];

	y = -1;
	while ((*matrix)[++y])
	{
		if ((*matrix)[y][0] == '$' && (*matrix)[y][1])
		{
			if ((*matrix)[y][1] == '?')
			{
				arr[1] = shell->exit_status > 255 ? ft_itoa(WEXITSTATUS(shell->exit_status)) : ft_itoa(shell->exit_status);
				free((*matrix)[y]);
				(*matrix)[y] = ft_strdup(arr[1]);
				ft_free(&arr[1]);
			}
			else
			{
				arr[1] = get_env_value(env, &(*matrix)[y][1]);
				free((*matrix)[y]);
				(*matrix)[y] = ft_strdup(arr[1]);
			}
		}
		else if (ft_strchr((*matrix)[y], '$') && ((*matrix)[y][1]))
			expand_util(matrix, y, arr[0], env);
	}
}

static char	*process_expansion_helper(t_env *env, char *result, char *temp)
{
	char	*value;

	value = get_env_value(env, temp);
	free(temp);
	if (value)
		result = ft_strjoin_free(result, value, 0);
	else
		result = ft_strjoin_free(result, "", 0);
	return (result);
}

static char	*process_expansion(char *str, t_env *env)
{
	char	*matrix[4];
	char	*tmp;

	matrix[1] = str;
	matrix[0] = ft_strdup("");
	matrix[1] = ft_strchr(matrix[1], '$');
	while (matrix[1])
	{
		matrix[2] = matrix[1];
		if (matrix[2] > str)
		{
			matrix[3] = ft_substr(str, 0, matrix[2] - str);
			matrix[0] = ft_strjoin_free(matrix[0], matrix[3], 3);
		}
		else
		{
			free(matrix[0]);
			free(matrix[3]);
		}
		matrix[1]++;
		matrix[2] = matrix[1];
		while (*matrix[2] && (ft_isalnum(*matrix[2]) || *matrix[2] == '_'))
			matrix[2]++;
		matrix[3] = ft_substr(matrix[1], 0, matrix[2] - matrix[1]);
		tmp = matrix[0];
		matrix[0] = process_expansion_helper(env, matrix[0], matrix[3]);
		free(tmp);
		str = matrix[2];
		matrix[1] = ft_strchr(matrix[1], '$');
	}
	matrix[0] = ft_strjoin_free(matrix[0], str, 1);
	return (matrix[0]);
}
