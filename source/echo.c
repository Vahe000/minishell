/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:44:59 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/19 18:42:40 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt(void)
{
	ft_putstr_fd("\n", 1);
	return (1);
}

int	ft_echo(t_main *data)
{
	int	n_opt;
	int	i;

	n_opt = 0;
	i = 1;
	if (!data->cmd[i] && cnt() == 1)
		return (1);
	if (ft_strcmp(data->cmd[i], "-n") == 0)
	{
		if (!data->cmd[i + 1])
			return (1);
		n_opt = 1;
		i++;
	}
	while (data->cmd[i])
	{
		ft_putstr_fd(data->cmd[i], 1);
		if (data->cmd[i + 1] && data->cmd[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_opt == 0)
		write(1, "\n", 1);
	return (0);
}
