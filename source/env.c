/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:44:59 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/24 14:54:30 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *data)
{
	t_env	*node;

	node = data;
	while (node)
	{
		if (!node->value)
			return (0);
		else
		{
			if (ft_strcmp(node->key, "?") != 0)
				printf("%s=%s\n", node->key, node->value);
		}
		node = node->next;
	}
	return (0);
}
