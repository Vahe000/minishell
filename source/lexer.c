/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:06:04 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 14:55:40 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(t_main **head, char *line, t_env *envv)
{
	t_main	*node;
	char	**token;
	int		i;

	i = 0;
	token = smart_split(line, '|');
	while (token && token[i])
	{
		node = malloc(sizeof(t_main));
		node->read_line = ft_strdup(token[i]);
		node->next = NULL;
		ft_list_add_back(head, node);
		++i;
	}
	if (error_quote(line, &envv) || error_pipe(line, list_size(*head), &envv))
	{
		if (token[0] != 0)
			token_free((*head));
		ft_free_tox(line);
		free_arr(token);
		return (1);
	}
	free_arr(token);
	return (0);
}

void	data_allocate(t_main **node)
{
	t_main	*data;
	char	*str;

	data = *node;
	str = ft_strdup(data->read_line);
	data->counts.count_outfile = count_outfile(str);
	data->outfile = malloc(sizeof(char *) * (data->counts.count_outfile + 1));
	data->outfile[data->counts.count_outfile] = NULL;
	data->counts.count_heredoc = count_heredoc(str);
	data->heredoc = malloc(sizeof(char *) * (data->counts.count_heredoc + 1));
	data->heredoc[data->counts.count_heredoc] = NULL;
	data->counts.count_append = count_append(str);
	data->append = malloc(sizeof(char *) * (data->counts.count_append + 1));
	data->append[data->counts.count_append] = NULL;
	data->counts.count_infile = count_infile(str);
	data->infile = malloc(sizeof(char *) * (data->counts.count_infile + 1));
	data->infile[data->counts.count_infile] = NULL;
	free(str);
	str = 0;
}

void	ft_cmd_parsing(t_main	**node, char **strcut)
{
	char	**str_cmd;
	int		i;

	i = -1;
	str_cmd = NULL;
	str_cmd = smart_split(*strcut, ' ');
	while (str_cmd && str_cmd[++(*node)->counts.count_cmd])
		;
	(*node)->cmd = ft_calloc((*node)->counts.count_cmd + 1, sizeof(char *));
	while (str_cmd && str_cmd[++i])
		pars_cmd((*node), str_cmd[i]);
	free_arr(str_cmd);
}

void	ft_which_red(t_main	**node, char **strcut)
{
	int		i;

	i = 0;
	while (*strcut && (*strcut)[i])
	{
		if (ft_quote_ignore(strcut, &i))
			break ;
		if ((*strcut)[i] == '<' && (*strcut)[i + 1] != '<')
			pars_infile((*node), strcut, i);
		else if ((*strcut)[i] == '<' && (*strcut)[i + 1] == '<')
			pars_heredoc((*node), strcut, i);
		else if ((*strcut)[i] == '>' && (*strcut)[i + 1] != '>')
			pars_outfile((*node), strcut, i);
		else if ((*strcut)[i] == '>' && (*strcut)[i + 1] == '>')
			pars_append((*node), strcut, i);
		else
			++i;
	}
}

int	parser(t_main **node, t_env **envv, char *line)
{
	t_main	*data;
	char	*strcut;
	int		index;

	index = 0;
	data = *node;
	while (data != NULL)
	{
		strcut = ft_strdup(data->read_line);
		data_allocate(&data);
		data->counts.count_cmd = -1;
		ft_which_red(&data, &strcut);
		ft_cmd_parsing(&data, &strcut);
		free(strcut);
		strcut = 0;
		data->index = index;
		index++;
		data = data->next;
	}
	dedollar(node, envv);
	ft_which_matrix(node);
	return (errorcheck_red(node, envv, line));
}
