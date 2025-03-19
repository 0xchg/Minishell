/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:02 by welepy            #+#    #+#             */
/*   Updated: 2025/03/19 18:22:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	calculate_result_size_util(int *k, char *input,
	t_env *env, size_t *result_size)
{
	size_t	var_len;
	char	*env_value;
	char	*temp;

	var_len = 0;
	(*k)++;
	while (ft_isalnum(input[*k + var_len]) || input[*k + var_len] == '_')
		var_len++;
	temp = ft_strndup(input + *k, var_len);
	env_value = get_env_value(temp, env);
	free(temp);
	if (env_value)
		*result_size += ft_strlen(env_value);
	else
		*result_size += 0;
	*k += var_len - 1;
}

static size_t	calculate_result_size(char *input, t_env *env, int exit_status)
{
	size_t	result_size;
	int		k;

	k = -1;
	result_size = 0;
	while (input[++k])
	{
		if (input[k] == '$')
		{
			if (input[k + 1] == '?')
			{
				result_size += ft_strlen_free(ft_itoa(exit_status));
				k++;
			}
			else if (ft_isalpha(input[k + 1]) || input[k + 1] == '_')
				calculate_result_size_util(&k, input, env, &result_size);
			else
				result_size++;
		}
		else
			result_size++;
	}
	return (result_size);
}

static void	append_exit_status(char *result, size_t *j,
	int exit_status, size_t *i)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(exit_status);
	ft_strcpy(result + *j, exit_status_str);
	*j += ft_strlen(exit_status_str);
	*i += 2;
	ft_free(&exit_status_str);
}

static void	append_env_value(t_strings strings, size_t *j,
	size_t *i, t_env *env)
{
	size_t	var_len;
	char	*env_value;
	char	*temp;

	(*i)++;
	var_len = 0;
	while (ft_isalnum(strings.str1[*i + var_len])
		|| strings.str1[*i + var_len] == '_')
		var_len++;
	temp = ft_strndup(strings.str1 + *i, var_len);
	env_value = get_env_value(temp, env);
	free(temp);
	if (env_value)
	{
		ft_strcpy(strings.str2 + *j, env_value);
		*j += ft_strlen(env_value);
	}
	*i += var_len;
}

char	*expand(char *input, t_env *env, int exit_status)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = safe_malloc(calculate_result_size(input, env, exit_status) + 1);
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				append_exit_status(result, &j, exit_status, &i);
			else if (ft_isalpha(input[i + 1]) || input[i + 1] == '_')
				append_env_value((t_strings){.str1 = input, .str2 = result},
					&j, &i, env);
			else
				result[j++] = input[i++];
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
