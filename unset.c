/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:40:54 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/28 14:39:05 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_var(char *del_var, t_env **data)
{
	t_env *cur;
	t_env *del;

	cur = (*data);
	while (cur->next)
	{
		if (ft_strcmp(del_var, cur->next->key) == 0)
		{
			del = cur->next;
			if (!cur->next->next)
				cur->next = NULL;
			else
				cur->next = cur->next->next;
			free(del);
		}
		if (cur->next)
			cur = cur->next;
	}
}

int	unset_errors(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] >= 48 && arg[i] <= 57)
		return (1);
	while (i < ft_strlen(arg))
	{
		if ((arg[i] > 32 && arg[i] < 48) ||
		(arg[i] == 58 ) || arg[i] == 63 ||
		arg[i] == 59 || (arg[i] > 90 && arg[i] < 97) ||
		(arg[i] > 122 && arg[i] < 127) || arg[i] == 64)
			return (1);
		i++;
	}
	return (0);
}

int ft_unset(char **cmd, t_env **env)
{
	int		i;
	t_env	*cur;
	
	i = 1;
	cur = (*env);
	while (cmd[i])
	{
		if (unset_errors(cmd[i]) == 0)
			next_var(&cmd[i][0], env);
		else
			ft_putstr_fd("not a valid identifier\n", 2);
		i++;
	}
	return (0);
}