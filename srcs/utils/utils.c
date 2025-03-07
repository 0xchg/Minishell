/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:08:38 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/07 10:54:05 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*matrix[2];
	char	**paths;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		matrix[1] = ft_strjoin(paths[i], "/");
		matrix[0] = ft_strjoin(matrix[1], cmd);
		ft_free(&matrix[1]);
		if (access(matrix[0], F_OK) == 0)
		{
			free_matrix(paths);
			return (matrix[0]);
		}
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

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	matrix = malloc(sizeof(char *) * (i + 1));
	tmp = env;
	i = 0;
	while (tmp)
	{
		matrix[i] = ft_strjoin(tmp->name, "=");
		matrix[i] = ft_strjoin(matrix[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

char	*clean_string(char *str)
{
	int		tab[2];
	char	*cleaned_str;

	tab[0] = 0;
	tab[1] = 0;
	while (str[tab[0]])
	{
		if (str[tab[0]] != '\"' || str[tab[0]] != '\'')
			tab[1]++;
		tab[0]++;
	}
	cleaned_str = (char *)malloc(sizeof(char) * (tab[1] + 1));
	if (!cleaned_str)
		return (NULL);
	tab[0] = -1;
	tab[1] = 0;
	while (str[++tab[0]])
	{
		if (str[tab[0]] == '\"' || str[tab[0]] == '\'')
			tab[0]++;
		cleaned_str[tab[1]] = str[tab[0]];
		tab[1]++;
	}
	cleaned_str[tab[0]] = '\0';
	return (cleaned_str);
}

char	*remove_quotes(char *str)
{
	size_t	len;

	if (str == NULL || strlen(str) < 2)
		return (str);
	len = ft_strlen(str);
	if ((str[0] == '"' || str[0] == '\'') \
		&& (str[len - 1] == '"' || str[len - 1] == '\''))
	{
		str++;
		str[len - 2] = '\0';
	}
	return (str);
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
