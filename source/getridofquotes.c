/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getridofquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:32:07 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/31 14:51:55 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_which_quote_is_first(char **line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line && line[i])
	{
		if (line[i][0] == '$')
			j = 1;
		if (line[i][0 + j] == '\'')
			return (111);
		else if (line[i][0 + j] == '\"')
			return (222);
		++i;
	}
	return (0);
}

void	get_rid_of_quotes(char **matrix, char *which_quot)
{
	int		i;
	char	*str;

	i = 0;
	while (matrix && (matrix)[i])
	{
		if (matrix[i][0] == which_quot[0] || matrix[i][0] == '$')
		{
			if (matrix[i][0] == '$')
				str = ft_strdup((matrix)[i] + 1);
			else
				str = ft_strdup((matrix)[i]);
			free(matrix[i]);
			matrix[i] = ft_strtrim(str, which_quot);
			free(str);
			str = 0;
		}
		i++;
	}
}

void	ft_which_matrix(t_main **head)
{
	if (ft_which_quote_is_first((*head)->cmd) == 222)
		get_rid_of_quotes(((*head)->cmd), "\"");
	else if (ft_which_quote_is_first((*head)->cmd) == 111)
		get_rid_of_quotes(((*head)->cmd), "\'");
	get_rid_of_quotes(((*head)->infile), "\"");
	get_rid_of_quotes(((*head)->outfile), "\"");
	get_rid_of_quotes(((*head)->append), "\"");
	get_rid_of_quotes(((*head)->heredoc), "\"");
	get_rid_of_quotes(((*head)->infile), "\'");
	get_rid_of_quotes(((*head)->outfile), "\'");
	get_rid_of_quotes(((*head)->append), "\'");
	get_rid_of_quotes(((*head)->heredoc), "\'");
}

int	ft_quote_ignore(char **str, int *i)
{
	while ((*str)[*i] == '"')
	{
		while ((*str)[++*i] != '"')
			;
		if ((*str)[*i])
			++*i;
	}
	while ((*str)[*i] == '\'')
	{
		while ((*str)[++*i] != '\'')
			;
		if ((*str)[*i])
			++*i;
	}
	if (!((*str)[*i]))
		return (1);
	else
		return (0);
}
