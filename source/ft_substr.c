/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:53:09 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/14 17:53:32 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	slen;

	i = 0;
	if (!s || !*s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		len = 0;
	else if (slen - start < len)
		len = slen - start;
	str = malloc(sizeof(char) * (len + 1));
	while (s[start + i] && len > i)
	{
		slen = ft_strlen(s);
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strcut(const char *src, unsigned int index, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!src || !*src)
		return (0);
	str = malloc(sizeof(char) * ((ft_strlen(src) - len + 1)));
	i = 0;
	j = 0;
	while (str && src && src[i])
	{
		if (i == index)
			i += len;
		if (src[i] == '\0')
			break ;
		str[j++] = src[i++];
	}
	str[j] = '\0';
	return (str);
}
