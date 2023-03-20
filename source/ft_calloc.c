/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:20:19 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/24 21:51:52 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

static void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = s;
	ft_memset (str, '\0', n);
}

void	*ft_calloc(size_t c, size_t s)
{
	void	*res;

	res = malloc (c * s);
	if (res == 0)
		return (res);
	ft_bzero (res, c * s);
	return (res);
}
