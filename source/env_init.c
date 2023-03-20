/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:17:40 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/26 14:56:54 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_to_list(t_env **l_env, char **env)
{
	int		i;
	t_env	*node;
	char	**tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		if (ft_strcmp(tmp[0], "OLDPWD") == 0)
			i++;
		else
		{
			node = malloc(sizeof(t_env));
			node->key = ft_strdup(tmp[0]);
			node->value = ft_strdup(tmp[1]);
			node->next = NULL;
			ft_lstadd_back(l_env, node);
			i++;
		}
		free_arr(tmp);
		tmp = NULL;
	}
}

char	**list_to_env(t_env *envv)
{
	int		i;
	char	**arr;
	char	*s1;
	t_env	*cur;

	s1 = NULL;
	cur = envv;
	arr = malloc(sizeof(char *) * ft_lstsize(envv) + 1);
	i = 0;
	while (cur->next)
	{
		arr[i] = ft_strjoin(cur->key, "=");
		if (cur->value)
		{
			s1 = ft_strdup(arr[i]);
			free(arr[i]);
			arr[i] = ft_strjoin(s1, cur->value);
			free(s1);
		}
		i++;
		cur = cur->next;
	}
	arr[i] = 0;
	return (arr);
}

void	change_shlvl(t_env *data)
{
	char	*val;

	val = NULL;
	while (data->next)
	{
		if (ft_strcmp(data->key, "SHLVL") == 0)
		{
			val = ft_strdup(data->value);
			free(data->value);
			data->value = ft_itoa(ft_atoi(val) + 1);
			free(val);
			return ;
		}
		data = data->next;
	}
}
