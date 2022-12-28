/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:02:14 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/26 13:17:56 by vasargsy         ###   ########.fr       */
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

// static void	*str_free(char **str, size_t i)
// {
// 	while (i >= 0)
// 	{
// 		free(str[i]);
// 		i--;
// 	}
// 	free(str);
// 	return (0);
// }


char	**ft_split_export(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	str = malloc(sizeof (char *) * (ft_strlen(s) + 1));
	if (s == 0 || str == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			str[0] = word_fill(s, 0, i);
			str[1] = word_fill(s, i + 1, (ft_strlen(s) - i));
			str[2] = 0;
			return (str);
		}
		i++;
	}
	str[0] = word_fill(s, 0, ft_strlen(s));
	str[1] = 0;
	return (str);
}