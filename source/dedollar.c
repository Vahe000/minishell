/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dedollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:56:35 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/24 12:32:19 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize(int *i, int *j)
{
	*i = -1;
	*j = 0;
}

void	dedollar(t_main **n, t_env **ennv)
{
	int		i;
	int		j;

	ft_initialize(&i, &j);
	while ((*n)->cmd && (*n)->cmd[++i] != NULL)
	{
		if (ft_dollar_here((*n)->cmd[i]))
			continue ;
		if ((*n)->cmd && (*n)->cmd[i] && (*n)->cmd[i][j] == '\'')
		{
			while ((*n)->cmd[i][++j] && (*n)->cmd[i][j] != '\'')
				;
			++j;
		}
		while ((*n)->cmd && (*n)->cmd[i] && (*n)->cmd[i][j])
		{
			if ((*n)->cmd && (*n)->cmd[i] && (*n)->cmd[i][j] == '$'
			&& ((*n)->cmd[i][j + 1] == '_' || ft_isa((*n)->cmd[i][j + 1]) == 1))
				ft_check_for_change(n, ennv, i, j);
			if ((*n)->cmd[i] == NULL || (*n)->cmd[i][j] == '\0')
				break ;
			++j;
		}
		j = 0;
	}
}
