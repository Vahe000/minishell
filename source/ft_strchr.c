/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:21:43 by leyeghia          #+#    #+#             */
/*   Updated: 2022/11/15 10:53:16 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (!(c >= 0 && c <= 127))
		return (0);
	while (str && (str[i] || c == 0))
	{
		if (str[i] == c)
			return (str[i]);
		i++;
	}
	return (0);
}
