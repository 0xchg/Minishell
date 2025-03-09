/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:16:24 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/09 15:14:46 by welepy           ###   ########.fr       */Z
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minihell.h"

// void	debug(t_token *token);

static bool	read_input(t_shell *shell)
{
	char	*raw_input;
	char	*pwd;
	char	*user;

	user = getenv("USER");
	if (!user)
		user = ft_strdup("");
	pwd = safe_malloc(PATH_MAX);
	getcwd(pwd, PATH_MAX);
	printf("┌[%s] - [%s]\n", user, pwd);
	raw_input = readline("└─[$] ");
	if (!raw_input)
	{
		ft_putstr_fd("exit\n", 2);
		ft_free(&shell->path);
		exit(0);
	}
	if (*raw_input)
		add_history(raw_input);
	if (all_spaces(raw_input))
	{
		ft_free(&raw_input);
		return (false);
	}
	shell->input = ft_strtrim(raw_input, " \t\n");
	ft_free(&raw_input);
	ft_free(&pwd);
	return (true);
}

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
	shell->exit_status = 0;
	shell->array = NULL;
	shell->flag = true;
	shell->env = convert_env(env);
	shell->path = get_path(shell->env);
	shell->token = NULL;
	shell->pipe = NULL;
}

void	repl(t_shell *shell)
{
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		if (!read_input(shell))
			continue ;
		add_history(shell->input);
		parse(shell);
		if (shell->flag)
			executer(shell, shell->token);
		free_tokens(shell->token);
		ft_free(&shell->input);
		free_matrix(shell->array);
		// debug(shell->token);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	if (ac == 1)
	{
		shell = malloc(sizeof(t_shell));
		init_shell(shell, env);
		repl(shell);
		free(shell);
	}
	else
		ft_fprintf(2, "%s do not receive argument!\n", av[0]);
	return (0);
}
/*
void	debug(t_token *token)
{
	t_token	*head;

	head = token;
	while (head)
	{
		// printf("value: %s, type: %s\n", token->value,
		// token = token->next;
		printf("%s, type: %s\n", head->value, token_kind_string(head->type));
		// else
		// 	printf("type: %s\n", token_kind_string(head->type));
		head = head->next;
	}
	printf("\n");
}*/
