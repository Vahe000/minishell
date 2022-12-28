/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:44:59 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/19 14:13:30 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **data)
{
	t_env	*node;

	node = *data;
	while (node->next)
	{
		if (!node->value)
			return (0);
		else
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	if (!node->value)
		return (0);
	else
		printf("%s=%s\n", node->key, node->value);
	return (0);
}