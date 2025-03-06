/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:52:15 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/06 19:15:02 by welepy           ###   ########.fr       */
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
	(*matrix)[y] = ft_strdup(arr);
}

void	expand(char ***matrix, t_env *env, t_shell *shell)
{
	int		y;
	char	*arr[2];

	y = -1;
	while ((*matrix)[++y])
	{
		if ((*matrix)[y][0] == '$')
		{
			if ((*matrix)[y][1] == '?')
			{
				arr[1] = ft_itoa(shell->exit_status);
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
		else if (ft_strchr((*matrix)[y], '$') && ((*matrix)[y][0] != '\''))
			expand_util(matrix, y, arr[0], env);
	}
}

static char	*process_expansion_helper(t_env *env, char *result, char *temp)
{
	char	*value;

	value = get_env_value(env, temp);
	free(temp);
	if (value)
		result = ft_strjoin_free(result, value);
	else
		result = ft_strjoin_free(result, "");
	return (result);
}

static char	*process_expansion(char *str, t_env *env)
{
	char	*result;
	char	*start;
	char	*end;
	char	*temp;

	start = str;
	result = ft_strdup("");
	while ((start = ft_strchr(start, '$')))
	{
		end = start;
		if (end > str)
		{
			temp = ft_substr(str, 0, end - str);
			result = ft_strjoin_free(result, temp);
		}
		start++;
		end = start;
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
		temp = ft_substr(start, 0, end - start);
		result = process_expansion_helper(env, result, temp);
		str = end;
	}
	result = ft_strjoin_free(result, str);
	return (result);
}

t_env	*convert_env(char **env)
{
	t_env	*list;
	t_env	*new;
	int		i;

	list = NULL;
	i = 0;
	while (env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
		{
			ft_lstclear((t_list **)&list, free);
			return (NULL);
		}
		new->name = ft_strndup(env[i], ft_strcspn(env[i], "="));
		new->value = ft_strdup(env[i] + ft_strcspn(env[i], "=") + 1);
		new->next = NULL;
		ft_lstadd_back((t_list **)&list, (t_list *)new);
		i++;
	}
	return (list);
}

char	*get_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
