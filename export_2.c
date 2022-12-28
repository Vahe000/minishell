/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:58:52 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/28 14:26:43 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			cur->value = ft_strjoin(cur->value, value);
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
		if ((str[i] > 32 && str[i] < 43) || str[i] == 63 ||
		(str[i] == 58 ) || (str[i] > 43 && str[i] < 48) ||
		str[i] == 59 || (str[i] > 90 && str[i] < 97) ||
		(str[i] > 122 && str[i] < 127) || str[i] == 64)
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
	if (str[i - 2] == '+' || metachars_in_str(str) == 1)
	{
		error = "not a valid identifier\n";
		ft_putstr_fd(error, 2);	
		return (1);		
	}
	return (0);
}
int	add_check(char *key, char *value, t_env **data)
{
	int i;

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