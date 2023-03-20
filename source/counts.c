/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:30:21 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/24 21:29:00 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_infile(char *str)
{
	int		count;
	int		i;
	char	*strcut;

	count = 0;
	i = -1;
	strcut = str;
	while (strcut && strcut[++i])
	{
		ft_quote_ignore(&strcut, &i);
		if (!strcut[i])
			break ;
		if (strcut[i] == '<' && strcut[i + 1] == '<')
			while (strcut[i] == '<')
				++i;
		if (strcut[i] == '\0')
			break ;
		if (strcut[i] == '<' && strcut[i + 1] != '<')
			++count;
	}
	return (count);
}

int	count_outfile(char *str)
{
	int		count;
	int		i;
	char	*strcut;

	count = 0;
	i = -1;
	strcut = str;
	while (strcut && strcut[++i])
	{
		ft_quote_ignore(&strcut, &i);
		if (!strcut[i])
			break ;
		if (strcut[i] == '>' && strcut[i + 1] == '>')
			while (strcut[i] == '>')
				++i;
		if (strcut[i] == '\0')
			break ;
		if (strcut[i] == '>' && strcut[i + 1] != '>')
			++count;
	}
	return (count);
}

int	count_heredoc(char *str)
{
	int		count;
	int		i;
	char	*strcut;

	count = 0;
	i = -1;
	strcut = str;
	while (strcut && strcut[++i])
	{
		ft_quote_ignore(&strcut, &i);
		if (!strcut[i])
			break ;
		if (strcut[i] == '<' && strcut[i + 1] == '<')
			++count;
		while (strcut[i] == '<')
			++i;
		if (strcut[i] == '\0')
			break ;
	}
	return (count);
}

int	count_append(char *str)
{
	int		count;
	int		i;
	char	*strcut;

	count = 0;
	i = -1;
	strcut = str;
	while (strcut && strcut[++i])
	{
		ft_quote_ignore(&strcut, &i);
		if (!strcut[i])
			break ;
		if (strcut[i] == '>' && strcut[i + 1] == '>')
			++count;
		while (strcut[i] == '>')
			++i;
		if (strcut[i] == '\0')
			break ;
	}
	return (count);
}
