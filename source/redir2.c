/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:11:46 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/31 14:54:44 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_print(char **s, int fd)
{
	write(fd, *s, ft_strlen(*s));
	write(fd, "\n", 1);
	free(*s);
	*s = NULL;
}

void	heredoc_dup(int fd, char **file, int flag)
{
	if (flag == 1)
	{
		close(fd);
		fd = open((*file), O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	unlink(*file);
	free(*file);
}

int	ft_break(char *s, char *str)
{
	if (!s)
	{
		ft_free_tox(s);
		return (1);
	}
	if (ft_strcmp(str, s) == 0)
	{
		ft_free_tox(s);
		return (1);
	}
	return (0);
}

void	heredoc_redirect(char *str, t_main **node)
{
	char	*s;
	int		fd;
	char	*file;

	file = ft_strjoin(".hd", str);
	str += 2;
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		s = readline("heredoc: ");
		if (g_exit_status == 26354)
		{
			g_exit_status = 0;
			(*node)->c_flag = 777;
			ft_free_tox(s);
			ft_free_tox(file);
			close(fd);
			return ;
		}
		if (ft_break(s, str))
			break ;
		heredoc_print(&s, fd);
	}
	heredoc_dup(fd, &file, 1);
}

void	heredoc_no_redirect(char *str)
{
	char	*s;
	int		fd;
	char	*file;

	file = ft_strjoin(".hd", str);
	str += 2;
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		s = readline("heredoc: ");
		if (g_exit_status == 26354)
		{
			g_exit_status = 0;
			free(s);
			close(fd);
			return ;
		}
		if (!s)
			return ;
		if (ft_strcmp(str, s) == 0)
			break ;
		heredoc_print(&s, fd);
	}
	heredoc_dup(fd, &file, 0);
}
