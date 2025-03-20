/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:08:38 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/19 18:25:23 by codespace        ###   ########.fr       */
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

char	**env_to_matrix(t_env *env)
{
	t_env	*tmp;
	char	**matrix;
	int		i;
	char	*temp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	matrix = safe_malloc(sizeof(char *) * (i + 1));
	tmp = env;
	i = -1;
	while (tmp)
	{
		matrix[++i] = ft_strjoin(tmp->name, "=");
		temp = ft_strjoin(matrix[i], tmp->value);
		ft_free(&matrix[i]);
		matrix[i] = temp;
		tmp = tmp->next;
	}
	matrix[++i] = NULL;
	return (matrix);
}

char	*remove_quotes(const char *str)
{
	size_t	len;
	size_t	new_len;
	char	*new_str;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		new_len = len - 2;
		new_str = safe_malloc(new_len + 1);
		strncpy(new_str, str + 1, new_len);
		new_str[new_len] = '\0';
		return (new_str);
	}
	return (strdup(str));
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		ft_free(&head->value);
		if (head)
		{
			free(head);
			head = NULL;
		}
		head = tmp;
	}
}

/*char	*eliminate_space_from_str(char *str)
{
	int	i = 0;
	int j = 0;
	char *new_str;

	while (ft_isspace(str[i]))
		i++;
	new_str = malloc(sizeof(str) + 1);
	while (str[i] && str[i] != ' ')
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return(new_str);
}*/
