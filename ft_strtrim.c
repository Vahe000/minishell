/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:50:36 by leyeghia          #+#    #+#             */
/*   Updated: 2022/11/15 14:20:54 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;

	i = 0;
	if (s1 == 0 && set == 0)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) && i)
		i--;
	str = ft_substr(s1, 0, i + 1);
	if (!str)
		return (0);
	return (str);
}
