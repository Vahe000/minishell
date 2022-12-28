/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:24:35 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/23 15:39:13 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	list_free(t_env **list)
{
	t_env	*node;
	t_env	*temp;

	temp = *list;
	while (temp)
	{
		node = temp;
		temp = temp->next;
		free(node);
	}
	free(list);
}