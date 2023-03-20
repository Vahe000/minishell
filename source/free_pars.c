/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:36:30 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/31 14:55:57 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_free(t_main *list)
{
	t_main	*hook;
	t_main	*data;

	data = list;
	while (data)
	{
		hook = data->next;
		free(data->read_line);
		free(data);
		data = NULL;
		data = hook;
	}
	data = NULL;
}

void	free_str(char **line)
{
	int	i;

	if (!line)
		return ;
	i = -1;
	while (line[++i])
	{
		if (line[i])
		{
			free(line[i]);
			line[i] = 0;
		}
	}
	free(line);
	line = 0;
}

void	list_free_(t_main *list)
{
	t_main	*hook;
	t_main	*data;

	data = list;
	while (data)
	{
		hook = data->next;
		if (data->cmd)
			free_str(data->cmd);
		if (data->infile)
			free_str(data->infile);
		if (data->outfile)
			free_str(data->outfile);
		if (data->append)
			free_str(data->append);
		if (data->heredoc)
			free_str(data->heredoc);
		free(data->read_line);
		free(data);
		data = NULL;
		data = hook;
	}
	data = NULL;
}

void	pars_free(t_main **head, char **line)
{
	list_free_(*head);
	free(*line);
	*line = 0;
}

void	ft_dzeva(char **str0, char **str1, int index, int len)
{
	free(*str1);
	*str1 = ft_strcut(*str0, index, len);
	free(*str0);
	*str0 = 0;
}
