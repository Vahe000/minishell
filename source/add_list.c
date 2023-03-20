/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:27:25 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/24 11:27:38 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_add_back(t_main **lst, t_main *new)
{
	t_main	*testnode;

	if (*lst == NULL)
		*lst = new;
	else
	{
		testnode = *lst;
		while (testnode->next != NULL)
			testnode = testnode->next;
		testnode->next = new;
	}
}
