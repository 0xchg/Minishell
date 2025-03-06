/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:46:17 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/06 14:35:33 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static void	ft_cd_prev(char	*prev_path, t_shell *shell)
{
	if (!prev_path)
	{
		ft_fprintf(2, "cd: OLDPWD not set\n");
		shell->exit_status = 1;
		return ;
	}
	else
	{
		if (chdir(prev_path) == 0)
		{
			printf("%s\n", prev_path);
			shell->exit_status = 0;
		}
		else
		{
			perror("cd");
			shell->exit_status = 1;
		}
	}
}

static void	ft_cd_aux(t_token *current, char *cur_path, t_shell *shell)
{
	char	*path;
	char	*new_path;

	path = ft_strjoin(cur_path, "/");
	new_path = ft_strjoin(path, current->value);
	ft_free(&path);
	if (*current->value == '~')
	{
		ft_free(&new_path);
		new_path = ft_strjoin(getenv("HOME"), current->value + 1);
	}
	if (chdir(new_path) == -1)
	{
		printf("cd: %s: No such file or directory\n", current->value);
		shell->exit_status = 1;
	}
	shell->exit_status = 0;
	ft_free(&new_path);
	ft_free(&cur_path);
}

static void	too_many_args(char *cur_path, t_shell *shell)
{
	ft_putstr_fd("cd: too many arguments\n", 2);
	ft_free(&cur_path);
	shell->exit_status = 1;
}

void	ft_cd(t_token *current, t_shell *shell)
{
	char		*cur_path;
	static char	*prev_path;
	t_token		*token;

	token = current->next;
	if (!token)
	{
		chdir(getenv("HOME"));
		return ;
	}
	cur_path = getcwd(NULL, 0);
	if (token->next)
	{
		too_many_args(cur_path, shell);
		return ;
	}
	if (ft_strcmp(token->value, "-") == 0)
	{
		ft_cd_prev(prev_path, shell);
		ft_free(&prev_path);
		prev_path = ft_strdup(cur_path);
		return ;
	}
	ft_cd_aux(token, cur_path, shell);
}
