/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:51:01 by vasargsy          #+#    #+#             */
/*   Updated: 2022/11/03 19:02:53 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env	*ft_lstlast(t_env *lst)
{
	if (lst == 0)
		return (0);
	while (lst -> next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tsl;

	tsl = *lst;
	if (!tsl)
	{
		*lst = new;
		return ;
	}
	tsl = ft_lstlast(*lst);
	tsl->next = new;
}
