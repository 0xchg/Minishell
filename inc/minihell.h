/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchingi <mchingi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:16:19 by mchingi           #+#    #+#             */
/*   Updated: 2025/03/23 17:02:19 by mchingi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H
# define PATH_MAX   4096

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include <stdbool.h> 

//----------------------------- Structs ---------------------------------------/

typedef struct s_strings	t_strings;
typedef t_strings			t_s;

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

typedef struct s_shell
{
	bool	flag;
	int		exit_status;
	char	*input;
	char	*path;
	char	**array;
	t_env	*env;
	t_token	*token;
	t_pipe	*pipe;
}		t_shell;

//------------------------------- Redirections -------------------------------/
bool		is_redirection(t_type type);
void		redirect_input(t_token *token, t_shell *shell);
void		redirect_output(t_token *token, t_shell *shell);
void		redirect_output_append(t_token *token, t_shell *shell);
void		redirect_here_doc(t_token *token, t_shell *shell);
void		execute_redirections(t_token *token, t_shell *shell);
void		redirect_builtins(t_shell *shell, t_token *tokens);
//----------------------------- Here Document --------------------------------/
void		here_doc(char *str);
//-------------------------------- Executer ----------------------------------/
int			executer(t_shell *shell, t_token *tokens);
void		execute_command(t_token *token, t_shell *shell);
void		execute_full_command(char **args, char **env, int in, int out);
void		execute_builtins(t_shell *shell, t_token *token);
void		execute_cmd_in_pipe(t_token *token, t_shell *shell, int in,
				int out);
void		ft_dup3(int fd, int fd2);
void		command_executer(t_shell *shell, t_token *tokens);
void		pipe_executer(t_shell *shell, t_token *token, t_pipe *pip,
				t_type type);
char		*find_path(char *cmd, char **envp);
char		**tokenize_command(t_token *token);

//--------------------------------- Tokens -----------------------------------/
bool		is_command(char *value, char *path);
void		identify_tokens(t_token *tokens, char *path);
void		token_sequence(t_token *tokens);
void		free_tokens(t_token *head);
char		*token_kind_string(t_type type);
t_token		*tokenize_array(char **array);
t_token		*new_token(char *value, t_type type);
//--------------------------------- Parse -------------------------------------/
bool		validate_quote_number(char *input);
void		parse(t_shell *shell);
int			word_count(char *input);
char		*get_path(t_env *env);
char		*remove_quotes(const char *str);
char		*extract_quote(char **input);
char		*extract_operator(char **input, t_shell *shell);
char		**env_to_matrix(t_env *env);
t_env		*convert_env(char **env);

//-------------------------------- Builtins ----------------------------------/
void		ft_cd(t_token *current, t_shell *shell);
void		ft_pwd(t_token *token, t_shell *shell);
int			ft_exit(t_shell *shell, t_token *token);
void		ft_env(t_env *env, t_token *token, t_shell *shell, bool declare);
void		ft_export(t_env *env, t_token *token, t_shell *shell);
void		ft_unset(t_env *env, t_token *token, t_shell *shell, bool flag);
void		ft_echo(t_token *token, t_shell *shell);

//--------------------------- VALIDATORS / VERIFICATIONS ---------------------/

bool		is_append(t_type token);
bool		is_greater(t_type token);
bool		is_lesser(t_type token);
bool		is_builtin(t_type type);
bool		is_builtin_or_command(t_type type);
int			here_doc_flag(t_token *token);
int			pipe_flag(t_token *token, t_shell *shell);
int			redirection_flag(t_token *token);

//-------------------------------- ANYTHING ----------------------------------/
void		error_message(char *str);
void		signal_handler(int sig);

char		*expand(char *input, t_env *env, int exit_status);
void		process_signal_handler(int sig);
void		empty_input(t_shell *shell);
char		*get_env_value(char *name, t_env *env);
void		set_sigint(int *num, char write);
int			expand_flag(char *input, int i);
bool		echo_aux(t_token *token, bool *option, char *input);
long long	ft_atol(const char *str);

void		handle_sigint(int sig);

void		handle_arguments(t_token *temp);
void		handle_redirections(t_token **temp);
void		handle_options(t_token **temp, bool *option);

#endif
