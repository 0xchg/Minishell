/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:08:38 by mchingi           #+#    #+#             */
/*   Updated: 2025/04/06 20:11:43 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static bool	check_path(char *str, char ***paths)
{
	if (access(str, F_OK) == 0)
	{
		free_matrix(*paths);
		return (true);
	}
	return (false);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*matrix[2];
	char	**paths;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		matrix[1] = ft_strjoin(paths[i], "/");
		matrix[0] = ft_strjoin(matrix[1], cmd);
		ft_free(&matrix[1]);
		if (check_path(matrix[0], &paths))
			return (matrix[0]);
		ft_free(&matrix[0]);
	}
	free_matrix(paths);
	return (NULL);
}

bool	util(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				return (true);
		}
		if (str[i])
			i++;
	}
	return (false);
}

char	*removing_inside_quotes(const char *str)
{
	size_t	i;
	size_t	k;
	char	*string;

	i = 0;
	k = 0;
	string = malloc(ft_strlen(str) + 1);
	if (!string)
		return (NULL);
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			i++;
			continue ;
		}
		string[k++] = str[i++];
	}
	string[k] = '\0';
	return (string);
}

char	*remove_quotes(const char *str, bool flag, bool flag2)
{
	size_t	new_len;
	char	*new_str;

	if (ft_strlen(str) >= 2
		&& ((str[0] == '"' && str[ft_strlen(str) - 1] == '"')
			|| (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')))
	{
		if (ft_strlen(str) <= 4 && flag)
		{
			if ((ft_strlen(str) == 3 && is_char_operator(str[1]))
				|| (ft_strlen(str) == 4 && is_char_operator(str[1])
					&& is_char_operator(str[2])))
				return (ft_strdup(str));
		}
		new_len = ft_strlen(str) - 2;
		new_str = safe_malloc(new_len + 1);
		if (!new_str)
			return (NULL);
		ft_strncpy(new_str, str + 1, new_len);
		new_str[new_len] = '\0';
		return (new_str);
	}
	else if (util(str) && flag2)
		return (removing_inside_quotes(str));
	return (ft_strdup(str));
}
