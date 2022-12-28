/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:30:21 by leyeghia          #+#    #+#             */
/*   Updated: 2022/12/12 10:41:00 by leyeghia         ###   ########.fr       */
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
		if (strcut[i] == '<' && strcut[i + 1] == '<')
			while (strcut[i] == '<')
				++i;
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
		if (strcut[i] == '>' && strcut[i + 1] == '>')
			while (strcut[i] == '>')
				++i;
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
		if (strcut[i] == '<' && strcut[i + 1] == '<')
			++count;
		while (strcut[i] == '<')
			++i;
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
		if (strcut[i] == '>' && strcut[i + 1] == '>')
			++count;
		while (strcut[i] == '>')
			++i;
	}
	return (count);
}

int	count_dollar(char *str)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '$' && str[i + 1] != 32)
			++count;
	}
	return (count);
}

/* int	main(int ac, char **av)
{
	(void) ac;
	printf("%d\n", count_append(av[1]));
} */
