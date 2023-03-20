/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:58:52 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 14:45:51 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_key_join(char *key, char *value, t_env **head)
{
	t_env	*cur;
	char	*tmp;

	tmp = NULL;
	cur = *head;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
		{
			if (cur->value)
				tmp = ft_strdup(cur->value);
			else
				tmp = ft_strdup("");
			if (cur->value)
				free(cur->value);
			cur->value = ft_strjoin(tmp, value);
			free(tmp);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static int	metachars_in_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= 48 && str[i] <= 57)
		return (1);
	while (i < ft_strlen(str))
	{
		if ((str[i] > 32 && str[i] < 43) || str[i] == 63
			|| (str[i] == 58) || (str[i] > 43 && str[i] < 48)
			|| str[i] == 59 || (str[i] > 90 && str[i] < 95) || str[i] == 96
			|| (str[i] > 122 && str[i] < 127) || str[i] == 64)
			return (1);
		i++;
	}
	return (0);
}

int	valid_key(char *str)
{
	int		i;
	char	*error;

	i = -1;
	error = NULL;
	while (str[++i])
		;
	if (metachars_in_str(str) == 1)
	{
		error = "not a valid identifier\n";
		ft_putstr_fd(error, 2);
		return (1);
	}
	if (ft_strlen(str) > 2)
	{
		if (str[i - 2] == '+')
		{
			error = "not a valid identifier\n";
			ft_putstr_fd(error, 2);
			return (1);
		}
	}
	return (0);
}

int	add_check(char *key, char *value, t_env **data)
{
	int	i;

	i = -1;
	while (key[++i])
	{
		if (key[i] == '+')
		{
			key[i] = '\0';
			if (check_key_join(key, value, data) == 1)
				return (1);
		}
	}
	return (0);
}
