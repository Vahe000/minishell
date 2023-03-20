/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:47:26 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/24 12:11:41 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isa(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == '?')
		return (1);
	return (0);
}

int	list_size(t_main *head)
{
	int		count;
	t_main	*data;

	count = 0;
	if (head == NULL)
		return (0);
	data = head;
	while (data)
	{
		++count;
		data = data->next;
	}
	return (count);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	count_words(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str && str[i] && str[i] == ' ')
		++i;
	while (str && str[i])
	{
		++count;
		if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		else if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		while (str[i] && str[i] != ' ')
			++i;
		while (str[i] && str[i] == ' ')
			++i;
	}
	return (count);
}

int	ft_if_else(int a, int index, char *str)
{
	int	i;

	i = a;
	if (str && str[i + index] == '"')
	{
		++i;
		while (str[i + index] && str[i + index] != '"')
			++i;
		++i;
	}
	else
	{
		while (str && str[i + index] && !ft_strchr(METACHARS, str[i + index]))
			++i;
	}
	return (i);
}
