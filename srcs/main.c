/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:16:24 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/05 10:10:14 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minihell.h"

static bool	read_input(t_shell *shell)
{
	char	*raw_input;

	printf("┌[%s] - [%s]\n", getenv("USER"), getcwd(NULL, 0));
	raw_input = readline("└─> ");
	if (!raw_input)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (*raw_input)
		add_history(raw_input);
	if (all_spaces(raw_input))
	{
		ft_free(&raw_input);
		printf("┌[%s] - [%s]\n", getenv("USER"), getcwd(NULL, 0));
		return (false);
	}
	shell->input = ft_strtrim(raw_input, " \t\n");
	ft_free(&raw_input);
	return (true);
}

/*void	debug(t_token *token, int number_of_commands)
{
	t_token	*head;

	head = token;
	while (head)
	{
		// printf("value: %s, type: %s\n", token->value, token_kind_string(token->type));
		// token = token->next;
		// if (head->type == COMMAND || head->type == ARGUMENT || head->type == VARIABLE)
		printf("%s, type: %s\n", head->value, token_kind_string(head->type));
		// else
		// 	printf("type: %s\n", token_kind_string(head->type));
		head = head->next;
	}
	printf("Number of commands: %d\n", number_of_commands);
	printf("\n");
}*/

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
	// shell->path = NULL;
	shell->exit_status = 0;
	shell->ev = env;
	shell->array = NULL;
	shell->flag = true;
	// shell->num_of_cmds = 0;
	shell->env = convert_env(env);
	shell->path = get_path(shell->env);
	shell->token = NULL;
	shell->pipe = NULL;
}

void	repl(t_shell *shell)
{
	while(1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		if (!read_input(shell))
			continue ;
		add_history(shell->input);	
		parse(shell);
		if (shell->flag)
			executer(shell, shell->token);
		else
		{
			free_matrix(shell->array);
			ft_free(&shell->input);
			free_tokens(shell->token);
		}
		// debug(shell->token, shell->num_of_cmds);
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
		printf("%s do not receive argument!\n", av[0]);
	return (0);
}
