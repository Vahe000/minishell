/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:44:59 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/26 12:23:43 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_main *data)
{
	int	n_opt;
	int	i;

	n_opt = 0;
	i = 1;
	if (!data->cmd[i])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(data->cmd[i], "-n") == 0)
	{
		if (!data->cmd[i + 1])
			return ;
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
}