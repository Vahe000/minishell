/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:06:04 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/12 10:40:27 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_main **head, char *line)
{
	t_main	*data;
	int		i;
	char	**token;

	i = 0;
	data = malloc(sizeof(t_main));
	token = ft_split(line, '|');
	*head = data;
	while (token && token[i])
	{
		data->read_line = token[i];
		//data->cmd = ft_split(token[i], 32);
		data->next = malloc(sizeof(t_main));
		data = data->next;
		++i;
	}
	data->next = NULL;
}

void	data_allocate(t_main **node)
{
	t_main	*data;
	char	*str;

	data = *node;
	str = data->read_line;
	printf("str = %s\n", str);
	data->counts.count_heredoc = count_heredoc(str);
	data->heredoc = malloc(sizeof(char *) * (data->counts.count_heredoc + 1));
	data->counts.count_outfile = count_outfile(str);
	data->outfile = malloc(sizeof(char *) * (data->counts.count_outfile + 1));
	data->counts.count_append = count_append(str);
	data->append = malloc(sizeof(char *) * (data->counts.count_append + 1));
	data->counts.count_infile = count_infile(str);
	data->infile = malloc(sizeof(char *) * (data->counts.count_infile + 1));
	data->counts.count_dollar = count_dollar(str);
	printf("dolo = %d\n", data->counts.count_dollar);
	data->dollar = malloc(sizeof(char *) * (data->counts.count_dollar + 1));
}

void	parser(t_main **node)
{
	t_main	*data;
	int		i;
	char	*strcut;

	i = 0;
	data = *node;
	strcut = data->read_line;
	//while (data->next != NULL)
	//{
	data_allocate(&data);
	//data->dollar = malloc(sizeof(char *) * (count_dollar(strcut) + 1));
	while (strcut && strcut[i])
	{
		if (strcut[i] == '<' && strcut[i + 1] != '<')
			strcut = pars_infile(data, strcut, i);
		else if (strcut[i] == '<' && strcut[i + 1] == '<')
			strcut = pars_heredoc(data, strcut, i);
		else if (strcut[i] == '>' && strcut[i + 1] != '>')
			strcut = pars_outfile(data, strcut, i);
		else if (strcut[i] == '>' && strcut[i + 1] == '>')
			strcut = pars_append(data, strcut, i);
		else
			++i;
		//else if (strcut[i] == '$')
		//	strcut = pars_dollar(data, strcut, i);
	}
	data->counts.count_cmd = count_words(strcut);
	data->cmd = malloc(sizeof(char *) * (data->counts.count_cmd + 1));
	i = -1;
	while (strcut && strcut[++i])
	{
		if (ft_isspace(strcut))
			break ;
		while (strcut && strcut[i] == ' ')
			++i;
		if (strcut[i])
		{
			strcut = pars_cmd(data, strcut, i);
			i = -1;
		}
	}
	free(strcut);
	free(data->cmd);
	//	data = data->next;
	//}
}
