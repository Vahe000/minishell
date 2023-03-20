/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:54:01 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 18:04:22 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define METACHARS " |&()<>;\t\n"
# define UNEXPECTED " |&();\t\n"

extern int	g_exit_status;

typedef struct s_counts
{
	int	count_infile;
	int	count_outfile;
	int	count_heredoc;
	int	count_append;
	int	count_cmd;
}			t_counts;

typedef struct s_main
{
	char			*read_line;
	char			**cmd;
	char			**heredoc;
	char			**outfile;
	char			**infile;
	char			**append;
	int				index;
	int				lst_size;
	int				exit_status;
	int				infile_status;
	int				infile_error;
	int				m_flag;
	int				c_flag;
	t_counts		counts;
	struct s_main	*next;
}					t_main;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				exit_status;
}					t_env;

typedef struct s_merge
{
	t_main		*l_head;
	t_env		*v_env;
	char		*line;
	int			in_cpy;
	int			out_cpy;
}				t_merge;

int		builtin(t_main **data, t_env **node);
void	env_to_list(t_env **l_env, char **env);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	env_add_item(char *key, char *value, t_env **env);

int		lexer(t_main **head, char *line, t_env *envv);
int		parser(t_main **node, t_env **envv, char *line);

int		ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strcut(const char *src, unsigned int index, size_t len);
char	ft_strchr(const char *str, int c);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strdup(const char *s1);
int		ft_lstsize(t_env *lst);
void	ft_putstr_fd(char *s, int fd);
long	ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_isa(int c);
int		arr_len(char **str);

int		ft_pwd(void);
int		ft_export(char **cmd, t_env **env);
int		ft_echo(t_main *data);
int		ft_unset(char **cmd, t_env **data);
int		ft_cd(char **cmd, t_env **data);
int		ft_env(t_env *data);
int		ft_exit(char **cmd, t_env *env, int flag);
void	ft_list_add_back(t_main **lst, t_main *new);
void	*ft_calloc(size_t c, size_t s);

void	pars_outfile(t_main *data, char **str, int index);
void	pars_infile(t_main *data, char **str, int index);
void	pars_heredoc(t_main *data, char **str, int index);
void	pars_append(t_main *data, char **str, int index);
void	pars_cmd(t_main *data, char *str);

int		count_outfile(char *str);
int		count_infile(char *str);
int		count_append(char *str);
int		count_heredoc(char *str);
int		count_words(char *str);

void	free_arr(char **arr);
void	list_free(t_env **stack);

void	dedollar(t_main **node, t_env **ennv);
int		ft_dollar_here(char *str);
int		ft_len_for_dollar(t_main **head, int i, int j);
char	*ft_change_dollar(char *src, char *oldstr, char *newstr, int start);
void	ft_check_for_change(t_main **data, t_env **ennv, int i, int j);

char	**smart_split(char const *s, char c);
int		errorcheck_red(t_main **head, t_env **envv, char *line);
int		error_pipe(char *str, int tokens_count, t_env **envv);
int		error_quote(char *str, t_env **envv);
int		list_size(t_main *head);

int		env_add(char *new_var, t_env **env);
void	ft_swap_key(t_env *a, t_env *b);
void	ft_swap_value(t_env *a, t_env *b);
int		is_sorted(t_env *data);
void	sort_export(t_env *data);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	check_add(char *str, t_env *env);
int		valid_key(char *str);
char	**ft_split_export(char const *s, char c);
int		add_check(char *key, char *value, t_env **data);
int		check_key(char *key, char *value, t_env **head);
int		print_declare(t_env *node);

void	do_redir(t_main *node);
void	do_infile(t_main *node);
void	infile_redir(char *file, t_main *node);
void	infile_no_redir(char *file, t_main *node);
void	no_outfile(char *file);
void	outfile(char *file);
void	append_redir(char *file);
void	append_no_redir(char *file);
void	heredoc_redirect(char *str, t_main **node);
void	heredoc_no_redirect(char *str);

char	*cmd_to_acc(char **cmd, t_env **data);
int		execve_part(t_main *node, t_env **data);
char	**list_to_env(t_env *envv);
int		if_built_in(char *str);
int		is_digit(char *str);
char	**path_find(t_env *data);

void	handler(int sig);
void	ft_quit(int sig);
void	change_shlvl(t_env *data);
void	cnf_error(char *cmd);
void	exit_to_many(t_env *env);

void	pars_free(t_main **head, char **line);
void	ft_dzeva(char **str0, char **str1, int index, int len);
int		ft_if_else(int a, int index, char *str);
void	list_free_(t_main *list);
void	token_free(t_main *list);
void	ft_free_tox(char *cmd);
int		ft_quote_ignore(char **str, int *i);
void	ft_which_matrix(t_main **head);
char	*cmd_to_acc(char **cmd, t_env **data);

int		ft_mankapartez(t_main *node, char **new_env, char *cmd);
void	ft_statuses(t_env **envv, int *pid, int size);
void	ft_close_fd(int size, int (*fd)[2]);
void	ft_exec_pipe(t_main *head, t_env **envv);
void	ft_fd_dup_close(t_main *head, int size, int (*fd)[2]);
void	ft_pipe(t_main *head, t_env **envv, int size);

void	ft_print_exit(void);
void	ft_control_c(t_env **env);
void	execution(t_main *head, t_env **envv, int in_cpy, int out_cpy);
int		ft_start_main(t_env **envv, char **line);
void	winter_is_comming(char **envp, t_env **envv, int argc, char **argv);
void	ft_print_exit(void);
int		ft_fork(int	*pid, t_env **envv, int i);

#endif