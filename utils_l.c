/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:47:26 by vasargsy          #+#    #+#             */
/*   Updated: 2022/11/29 17:47:09 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	count_words(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		++i;
	while (str && str[i] && str[i])
	{
		++count;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			++i;
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			++i;
	}
	return (count);
}

char	*pars_dollar(t_main *data, char *str, int index)
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
	printf("cutstr_dollar = %s\n\n", cutstr);
	data->dollar[l] = ft_substr(str, index, i);
	printf("dollar[%d] = !%s!\n\n", l, data->dollar[l]);
	++l;
	return (cutstr);
}
