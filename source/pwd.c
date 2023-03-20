/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:54:05 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/18 22:55:03 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	c[1024];

	if (getcwd(c, 1024))
	{
		printf("%s\n", c);
		return (0);
	}
	else
		return (1);
}