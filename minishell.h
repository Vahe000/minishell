/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:54:01 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/28 13:23:10 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"

# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>


# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

# define METACHARS " |&()<>;\t\n"

typedef struct s_counts
{
	int	count_infile;
	int	count_outfile;
	int	count_heredoc;
	int	count_append;
	int	count_cmd;
	int	count_dollar;
}			t_counts;

typedef struct s_main
{
	// int				input;
	// int				output;
	// int				index;
	char			*read_line;
	char			**dollar;
	char			**cmd;
	char			**heredoc;
	char			**outfile;
	char			**infile;
	char			**append;
	t_counts		counts;
	struct s_main	*next;
}					t_main;

typedef struct s_env
{
	char			*key;
	char			*value;

	int				status;

	struct s_env	*next;
}					t_env;

void	ft_strtok(t_main *data);
void	builtin(t_main **data, t_env **node);
int		ft_pwd(void);
int		ft_env(t_env **data);
void	env_to_list(t_env **l_env, char **env);
void	ft_lstadd_back(t_env **lst, t_env *new);

void	lexer(t_main **head, char *line);
void	parser(t_main **node);

int		ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strcut(const char *src, unsigned int index, size_t len);
char	ft_strchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_isspace(char *str);

int		ft_export(char **cmd, t_env **env);
int		env_add(char *new_var, t_env **env);
void	ft_swap_key(t_env *a, t_env *b);
void	ft_swap_value(t_env *a, t_env *b);
int		is_sorted(t_env *data);
void	sort_export(t_env *data);
int		ft_strncmp(char *s1,char *s2, size_t n);
void	check_add(char *str, t_env *env);
int		valid_key(char *str);
char	**ft_split_export(char const *s, char c);
int		add_check(char *key, char *value, t_env **data);

void	heredoc_redir(char *limiter);
void	ft_echo(t_main *data);
void	ft_putstr_fd(char *s, int fd);
int		ft_unset(char **cmd, t_env **data);
int		ft_cd(char **cmd, t_env **data);

char	*pars_outfile(t_main *data, char *str, int index);
char	*pars_infile(t_main *data, char *str, int index);
char	*pars_heredoc(t_main *data, char *str, int index);
char	*pars_append(t_main *data, char *str, int index);
char	*pars_cmd(t_main *data, char *str, int index);
char	*pars_dollar(t_main *data, char *str, int index);

int		count_outfile(char *str);
int		count_infile(char *str);
int		count_append(char *str);
int		count_heredoc(char *str);
int		count_words(char *str);
int		count_dollar(char *str);

void	free_str(char **arr);
void	list_free(t_env **stack);

void	infile_redir(char *file);
void 	outfile(char *file);
void	append_redir(char *file);
void	heredoc_redirect(char *str);
char	*cmd_to_acc(char **cmd, t_env **data);

#endif