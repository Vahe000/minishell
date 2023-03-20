/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:24:35 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/22 17:02:39 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tox(char *cmd)
{	
	if (cmd != NULL)
	{
		free(cmd);
		cmd = 0;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
	arr = 0;
}

void	list_free(t_env **list)
{
	t_env	*node;
	t_env	*temp;

	temp = *list;
	while (temp)
	{
		node = temp;
		free(node->key);
		free(node->value);
		temp = temp->next;
		free(node);
	}
	free(list);
}
