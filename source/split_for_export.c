/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:02:14 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/19 19:03:55 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*word_fill(const char *s, size_t start, size_t len)
{
	size_t	i;
	char	*word;

	i = 0;
	word = malloc(len + 1);
	if (word == 0)
		return (0);
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = 0;
	return (word);
}

void	ft_lala(char ***str, char const *s, int i)
{
	if (s[i] == '=')
		(*str)[0] = word_fill(s, 0, i);
	else
		(*str)[0] = word_fill(s, 0, ft_strlen(s));
	(*str)[1] = 0;
}

char	**ft_split_export(char const *s, char c)
{
	int		i;
	char	**str;

	i = -1;
	str = malloc(sizeof (char *) * (ft_strlen(s) + 1));
	if (s == 0 || str == 0)
		return (0);
	while (s[++i])
	{
		if (s[i] == c)
		{
			if (s[i + 1])
			{
				str[0] = word_fill(s, 0, i);
				str[1] = word_fill(s, i + 1, (ft_strlen(s) - i));
				str[2] = 0;
			}
			else
				break ;
			return (str);
		}
	}
	ft_lala(&str, s, i);
	return (str);
}
