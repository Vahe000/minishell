/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:04:05 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 17:37:40 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialize_tmp(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[0][i])
	{
		if (tmp[0][i] == '+')
			tmp[0][i] = '\0';
		i++;
	}
}

int	env_add(char *new_var, t_env **env)
{
	t_env	*new_node;
	char	**tmp;

	tmp = ft_split_export(new_var, '=');
	if (check_key(tmp[0], tmp[1], env) == 0)
	{
		new_node = malloc(sizeof(t_env));
		if (!(new_node))
			return (1);
		new_node->key = ft_strdup(tmp[0]);
		if (tmp[1])
			new_node->value = ft_strdup(tmp[1]);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		ft_lstadd_back(env, new_node);
	}
	free_arr(tmp);
	return (0);
}

t_env	*lst_new_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	env_add_item(char *key, char *value, t_env **env)
{
	t_env	*new_node;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_node = lst_new_env(key, value);
	ft_lstadd_back(env, new_node);
}

int	ft_export(char **cmd, t_env **env)
{
	int		i;
	char	**tmp;

	i = 1;
	if (!cmd[i] && print_declare((*env)))
		return (0);
	while (cmd[i])
	{
		tmp = ft_split_export(cmd[i], '=');
		if (valid_key(tmp[0]) == 1)
		{
			free_arr(tmp);
			return (1);
		}
		if (add_check(tmp[0], tmp[1], env) == 0)
			env_add(cmd[i], env);
		free_arr(tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}
