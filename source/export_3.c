/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:11:27 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/19 19:14:41 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *key, char *value, t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	if (!key)
		return (0);
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (!value)
			{
				tmp->value = NULL;
				return (1);
			}
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_sorted(t_env *data)
{
	t_env	*cur;

	cur = data;
	while (data->next)
	{
		if (ft_strncmp(data->key, data->next->key, ft_strlen(data->key)) > 0)
			return (1);
		data = data->next;
	}
	data = cur;
	return (0);
}

int	print_declare(t_env *node)
{	
	sort_export(node);
	while (node)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(node->key, 1);
		if (node->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(node->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		node = node->next;
	}
	return (0);
}

void	sort_export(t_env *data)
{
	t_env	*cur;

	cur = data;
	while ((is_sorted(cur) == 1))
	{
		if (data->next == NULL)
			data = cur;
		if (ft_strncmp(data->key, data->next->key, ft_strlen(data->key)) > 0)
		{
			ft_swap_key(data, data->next);
			ft_swap_value(data, data->next);
		}
		data = data->next;
	}
	data = cur;
}
