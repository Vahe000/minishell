/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:17:40 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/22 17:04:33 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_elenm_list(const char *key, const char *value)
{
	t_env	*l_env;

	l_env = malloc(sizeof(t_env));
	l_env->key = (char *)key;
	l_env->value = (char *)value;
	l_env->status = 0;
	l_env->next = NULL;
	return (l_env);
}

void	env_to_list(t_env **l_env, char **env)
{
	int		i;
	t_env	*node;
	char	**tmp;

	i = 0;
	node = malloc(sizeof(t_env));
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		if (ft_strcmp(tmp[0], "OLDPWD") == 0)
			i++;
		else
		{
			node = new_elenm_list(tmp[0], tmp[1]);
			ft_lstadd_back(l_env, node);
			i++;
		}
	}
}