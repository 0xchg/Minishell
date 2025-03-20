/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:49:08 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/20 11:57:20 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minihell.h"

static	t_env	*arg_to_env(t_token *token)
{
	char	**temp;
	t_env	*current_env;

	temp = ft_split(token->value, '=');
	current_env = safe_malloc(sizeof(t_env));
	current_env->name = ft_strdup(temp[0]);
	if (temp[1])
		current_env->value = ft_strdup((temp[1]));
	else if (token->next && (token->next->type == DOUBLE_QUOTE || \
				token->next->type == SINGLE_QUOTE))
		current_env->value = ft_strdup(token->next->value);
	else
		current_env->value = NULL;
	current_env->next = NULL;
	free_matrix(temp);
	return (current_env);
}

t_env	*last_env(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*t;

	if (*env)
	{
		t = last_env(*env);
		t->next = new;
	}
	else
		*env = new;
}

static bool	export_error(t_token *head, t_shell *shell, int flag)
{
	if (head->next && !ft_strlen(head->next->value) && flag == 0)
	{
		shell->exit_status = 1;
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", \
				head->next->value);
		return (false);
	}
	if (head->next && head->next->type == OPTION && flag == 1)
	{
		shell->exit_status = 1;
		ft_fprintf(2, "export: this version doesn't support options");
		return (false);
	}
	return (true);
}

void	ft_export(t_env *env, t_token *token, t_shell *shell)
{
	t_env	*temp;
	t_token	*head;

	head = token;
	if (!head->next)
		ft_env(env, head, shell, true);
	if (!export_error(head, shell, 1))
		return ;
	if (!export_error(head, shell, 0))
		return ;
	head = head->next;
	while (head && (head->type == ARGUMENT))
	{
		if (head->value[0] == '=')
		{
			ft_fprintf(2, "export: `=%s': invalid identifier\n", temp->value);
			shell->exit_status = 2;
			return ;
		}
		temp = arg_to_env(head);
		ft_unset(env, head, shell, true);
		add_env(&env, temp);
		head = head->next;
	}
	shell->exit_status = 0;
}
