/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:16:19 by mchingi           #+#    #+#             */
/*   Updated: 2025/02/27 19:42:30 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H
# define PATH_MAX   4096

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"

// --------------     ATENÇÃO!  ------------------- /
#include <stdbool.h> 
# include <strings.h>
//--------------------------------------------- Structs -----------------------------------------------------/

typedef enum e_type
{
	HERE_DOC,
	LESSER,
	GREATER,
	APPEND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	BUILTINS,
	COMMAND,
	FULL_COMMAND,
	OPTION,
	ARGUMENT,
	IDENTIFIER
}		t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_pipe
{
	int		i;
	int		pipe_fd[2];
	int		input_fd;
	int		flag;
	char	**ev;
	pid_t	id;
}		t_pipe;

typedef struct	s_shell
{
	char	*input;
	char	*path;
	char	**ev;
	char	**array;
	bool	flag;
	int		num_of_cmds;
	t_env	*env;
	t_token	*token;
	t_pipe	*pipe;
}		t_shell;

//--------------------------------------------- Redirections -----------------------------------------------------/
void	redirect_input(t_token *token);
void	redirect_output(t_token *token);
void	redirect_output_append(t_token *token);
void	redirect_here_doc(t_token *token);
void	execute_redirections(t_token *token);
bool	is_redirection(t_type type);
//--------------------------------------------- Here Document -----------------------------------------------------/
void	here_doc(char *str);
//--------------------------------------------- Executer -----------------------------------------------------/
char	**tokenize_command(t_token *token);
int		executer(t_shell *shell, t_token *tokens);
char	*find_path(char *cmd, char **envp);
void	execute_command(t_token *token, char **env);
void	execute_builtins(t_shell *shell, t_token *token);
void    execute_cmd_in_pipe(t_token *token, t_pipe *pipes, int in, int out);
void	dup3(int fd, int fd2);
void	command_executer(t_shell *shell, t_token *tokens);

//--------------------------------------------- Tokens -----------------------------------------------------/
void	identify_tokens(t_token *tokens, char *path);
t_token	*tokenize_array(char **array);
bool 	is_command(char *value, char *path);
bool	is_builtin_or_command(t_type type);
bool	is_builtin(t_type type);
t_token	*new_token(char *value, t_type type);
void	token_sequence(t_token *tokens);
char	*token_kind_string(t_type type);
bool	is_append(t_type token);
bool	is_greater(t_type token);
bool	is_lesser(t_type token);
bool 	is_command2(char *value);

//--------------------------------------------- Parse -----------------------------------------------------/
int		word_count(char *input);
char	*extract_quote(char **input);
char	*extract_operator(char **input);
void	parse(t_shell *shell);
bool	validate_quote_number(char *input);
int		number_of_commands(t_token *tokens);
void	expand(char ***matrix, t_env *env);
t_env	*convert_env(char **env);
char	*get_path(t_env *env);
char	*clean_string(char *str);
char	*remove_quotes(char *str);

//--------------------------------------------- Builtins -----------------------------------------------------/
void	ft_cd(t_token *current);
void	ft_pwd(t_token *token);
void	ft_exit(t_shell *shell);
void	ft_env(t_env *env, t_token *token);
void	ft_export(t_env *env, t_token *token);
void	ft_unset(t_env *env, t_token *token);
void	ft_echo(t_token *token, t_shell *shell);


//--------------------------------------------- ANYTHING -----------------------------------------------------/
void	error_message(char *str);

#endif
