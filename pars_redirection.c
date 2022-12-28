/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:31:48 by leyeghia          #+#    #+#             */
/*   Updated: 2022/12/12 10:13:44 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pars_outfile(t_main *data, char *str, int index)//>
{
	int			i;
	static int	l = 0;

	i = 1;
	while (str[i + index] == ' ')
		++i;
	if (i != 1)	//#1 vor 0 len-ov nuyn toxy noric malloc chani
		str = ft_strcut(str, 1 + index, i - 1);//space-ery hanelu hamar
	i = 1;//#2 vor spacery haneluc heto iranc qanaky avel chmna 'i'-i mej
	if (str[i + index] == '"')
	{
		++i;
		while (str[i + index] && str[i + index] != '"')
			++i;
		++i;
	}
	else
		while (str[i + index] && !ft_strchr(METACHARS, str[i + index]))
			++i;
	data->outfile[l] = ft_substr(str, index, i);
	printf("outfile[%d] = !%s!\n\n", l, data->outfile[l]);
	++l;
	if (l == data->counts.count_outfile)
		l = 0;
	return (ft_strcut(str, index, i));
}

/* char	*pars_outfile(t_main *data, char *str, int index)
{
	int			i;
	char		*cutstr;
	static int	l = 0;

	i = 1;
	while (str[i + index] == ' ')
		++i;
	str = ft_strcut(str, 1 + index, i - 1);
	while (str[i + index] && !ft_strchr(METACHARS, str[i + index]))
		++i;
	cutstr = ft_strcut(str, index, i);
	printf("cutstr_outfile = %s\n\n", cutstr);
	data->outfile[l] = ft_substr(str, index, i);
	printf("outfile[%d] = !%s!\n\n", l, data->outfile[l]);
	++l;
	return (cutstr);
} */

char	*pars_infile(t_main *data, char *str, int index)
{
	int			i;
	static int	l = 0;

	i = 1;
	while (str[i + index] == ' ')
		++i;
	if (i != 1)
	{
		str = ft_strcut(str, 1 + index, i - 1);
		i = 1;
	}
	if (str[i + index] == '"')
	{
		++i;
		while (str[i + index] && str[i + index] != '"')
			++i;
		++i;
	}
	else
		while (str[i + index] && !ft_strchr(METACHARS, str[i + index]))
			++i;
	data->infile[l] = ft_substr(str, index, i);
	printf("infile[%d] = !%s!\n\n", l, data->infile[l]);
	++l;
	if (l == data->counts.count_infile)
		l = 0;
	return (ft_strcut(str, index, i));
}

char	*pars_heredoc(t_main *data, char *str, int index)
{
	int			i;
	int			j;
	static int	l = 0;

	i = 0;
	while (ft_strchr("<", str[i + index]))
		++i;
	j = i;
	while (str[i + index] == ' ')
		++i;
	if (i != j)
	{
		str = ft_strcut(str, j + index, i - j);
		i = j;
	}
	if (str[i + index] == '"')
	{
		++i;
		while (str[i + index] && str[i + index] != '"')
			++i;
		++i;
	}
	else
	{
		while (str[i + index] && !ft_strchr(METACHARS, str[i + index]))
			++i;
	}
	data->heredoc[l] = ft_substr(str, index, i);
	printf("heredoc[%d] = !%s!\n\n", l, data->heredoc[l]);
	++l;
	if (l == data->counts.count_heredoc)
		l = 0;
	return (ft_strcut(str, index, i));
}

char	*pars_append(t_main *data, char *str, int index)
{
	int			i;
	int			j;
	static int	l = 0;

	i = 0;
	while (ft_strchr(">", str[i + index]))
		++i;
	j = i;
	while (str[i + index] == ' ')
		++i;
	if (i != j)
	{
		str = ft_strcut(str, j + index, i - j);
		i = j;
	}
	if (str[i + index] == '"')
	{
		++i;
		while (str[i + index] && str[i + index] != '"')
			++i;
		++i;
	}
	else
		while (str[i + index] && !ft_strchr(METACHARS, str[i + index]))
			++i;
	data->append[l] = ft_substr(str, index, i);
	printf("append[%d] = !%s!\n\n", l, data->append[l]);
	++l;
	if (l == data->counts.count_append)
		l = 0;
	return (ft_strcut(str, index, i));
}

char	*pars_cmd(t_main *data, char *str, int index)
{
	int			i;
	static int	l = 0;

	i = 0;
	if (ft_isspace(str))
		return (NULL);
	if (str[i + index] == '"')
	{
		++i;
		while (str[i + index] && str[i + index] != '"')
			++i;
		++i;
	}
	else
		while (str[i + index] && !ft_strchr(METACHARS, str[i + index]))
			++i;
	data->cmd[l] = ft_substr(str, index, i);
	printf("cmd[%d] = !%s!\n\n", l, data->cmd[l]);
	++l;
	if (l == data->counts.count_cmd)
		l = 0;
	return (ft_strcut(str, index, i));
}
