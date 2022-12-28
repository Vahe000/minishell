/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:02:50 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/26 16:16:58 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void outfile(char *file)
{
	int fd;

	fd = open(file, O_RDONLY, 0644);
	if(fd < 0)
	{
		write(2,"no such a file or directoy\n",27);
		return ;
	}
	dup2(fd, 0);
	close(fd);
	
}

void	infile_redir(char *file)
{
	int fd;
	//printf("%s file",file);
	fd = open(++file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

void	append_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
}
void	heredoc_no_redirect(char *str)
{
	char	*s;
	int		fd;
	int		i;
	char	*file;

	file = ft_strjoin(".\7", str);
	i = 0;
	//str += 2;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '-')
		{
			printf("%s\n", "syntax error near unexpected token `<'");
			return ;
		}
		i++;
	}
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf(" nooo delim :%s\n",str);
	while (1)
	{
		s = readline("heredoc: ");
		if(!s)
			return ;
		if (strcmp(str, s) == 0)
			break ;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
		s = NULL;
	}

}

void	heredoc_redirect(char *str)
{
	char	*s;
	int		fd;
	int		i;
	char	*file;
	//int cpy = dup(0);

	file = ft_strjoin(".\7", str);
	i = 0;
	//str += 2;
/* 	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '-')
		{
			printf("%s\n", "syntax error near unexpected token `<'");
			return ;
		}
		i++;
	} */
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf(" delim :%s\n",str);
	while (1)
	{
		s = readline("heredoc: ");
		if(!s)
			return ;
		if (strcmp(str, s) == 0)
			break ;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
		s = NULL;
	}
	close(fd);
	fd = open(file, O_RDONLY);
	dup2(fd, 0);
	close(fd);
	unlink(file);
	free(file);
	//dup2(cpy,0);
}

void	heredoc_redir(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(ft_strjoin(".",limiter), O_WRONLY | O_CREAT | O_TRUNC);
	//limiter+=2;
	while(1)
	{
		line = readline("heredoc: ");
		if(!line)
			return ;
		if(!line[0])
			continue;
		if(ft_strcmp(line, limiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	close(fd);
	fd = open(ft_strjoin(".",limiter), O_RDONLY);
	dup2(fd, 0);
	close(fd);
	unlink(ft_strjoin(".",limiter));
	//free(limiter);
}