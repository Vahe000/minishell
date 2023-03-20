/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:56:34 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/16 03:36:13 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		++len;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		dest[j] = s2[i];
		i++;
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/* ft_strjoin(char *s1,char*s2 ,int flag)
{
	after join =>
	if(flag == 1)
		free(s1);
	else if (flag == 12)
		free(s1)
		free(s2)
	else if (flag == 2)
		free(s2);
	
} */