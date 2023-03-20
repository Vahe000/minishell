/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:02:50 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 19:04:43 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outfile(char *file)
{
	int	fd;

	fd = open(++file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

void	no_outfile(char *file)
{
	int	fd;

	fd = open(++file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);
}

void	infile_redir(char *file, t_main *node)
{
	int	fd;

	fd = open(++file, O_RDONLY, 0644);
	if (fd < 0)
	{
		if (node->infile_error != 1)
		{
			write(2, "No such file or directory\n", 27);
			node->infile_status = -1;
			return ;
		}
	}
	dup2(fd, 0);
	close(fd);
}

void	infile_no_redir(char *file, t_main *node)
{
	int	fd;

	fd = open(++file, O_RDONLY, 0644);
	if (fd < 0)
	{
		write(2, "No such file or directory\n", 27);
		node->infile_status = -1;
		node->infile_error = 1;
		return ;
	}
	close(fd);
}

void	append_redir(char *file)
{
	int	fd;

	file += 2;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
}
