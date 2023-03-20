/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:09:17 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/21 21:42:20 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cnf_error(char *cmd)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(&cmd[0], 2);
	ft_putstr_fd("\n", 2);
	exit (127);
}
