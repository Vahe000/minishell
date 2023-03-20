/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:31:48 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/24 12:03:13 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_outfile(t_main *data, char **str, int index)
{
	int			i;
	char		*newstr0;
	char		*newstr1;
	static int	l = 0;

	newstr0 = NULL;
	newstr1 = NULL;
	i = 1;
	newstr1 = ft_strdup(*str);
	while (newstr1[i + index] == ' ')
		++i;
	newstr0 = ft_strcut(newstr1, 1 + index, i - 1);
	i = ft_if_else(1, index, newstr0);
	data->outfile[l] = ft_substr(newstr0, index, i);
	++l;
	if (l == data->counts.count_outfile)
		l = 0;
	ft_dzeva(&newstr0, str, index, i);
	free(newstr1);
	newstr1 = 0;
}

void	pars_infile(t_main *data, char **str, int index)
{
	int			i;
	char		*newstr0;
	char		*newstr1;
	static int	l = 0;

	newstr0 = NULL;
	newstr1 = NULL;
	i = 1;
	newstr1 = ft_strdup(*str);
	while (newstr1[i + index] == ' ')
		++i;
	newstr0 = ft_strcut(newstr1, 1 + index, i - 1);
	i = ft_if_else(1, index, newstr0);
	data->infile[l] = ft_substr(newstr0, index, i);
	++l;
	if (l == data->counts.count_infile)
		l = 0;
	ft_dzeva(&newstr0, str, index, i);
	free(newstr1);
	newstr1 = 0;
}

void	pars_heredoc(t_main *data, char **str, int index)
{
	int			i;
	int			j;
	char		*newstr0;
	char		*newstr1;
	static int	l = 0;

	i = 0;
	newstr1 = ft_strdup(*str);
	while (ft_strchr("<", newstr1[i + index]))
		++i;
	j = i;
	while (newstr1[i + index] == ' ')
		++i;
	newstr0 = ft_strcut(newstr1, j + index, i - j);
	i = ft_if_else(j, index, newstr0);
	data->heredoc[l] = ft_substr(newstr0, index, i);
	++l;
	if (l == data->counts.count_heredoc)
		l = 0;
	ft_dzeva(&newstr0, str, index, i);
	free(newstr1);
	newstr1 = 0;
}

void	pars_append(t_main *data, char **str, int index)
{
	int			i;
	int			j;
	char		*newstr0;
	char		*newstr1;
	static int	l = 0;

	i = 0;
	newstr1 = ft_strdup(*str);
	while (ft_strchr(">", newstr1[i + index]))
		++i;
	j = i;
	while (newstr1[i + index] == ' ')
		++i;
	newstr0 = ft_strcut(newstr1, j + index, i - j);
	i = ft_if_else(j, index, newstr0);
	data->append[l] = ft_substr(newstr0, index, i);
	++l;
	if (l == data->counts.count_append)
		l = 0;
	ft_dzeva(&newstr0, str, index, i);
	free(newstr1);
	newstr1 = 0;
}

void	pars_cmd(t_main *data, char *str)
{
	static int	l = 0;

	data->cmd[l] = ft_strdup(str);
	++l;
	if (l == data->counts.count_cmd)
		l = 0;
}
