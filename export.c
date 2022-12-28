/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:04:05 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/28 14:27:47 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_declare(t_env *node)
{	
	sort_export(node);
	while (node)
	{
		printf("declare -x ");
		printf("%s", node->key);
		if (node->value)
		{
			printf("=\"");
			printf("%s", node->value);	
			printf("\"");
		}
		printf("\n");
		node = node->next;
	}
	return (0);
}

void	sort_export(t_env *data)
{
	int		i;
	t_env	*cur;
	
	i = 0;
	cur = data;
	while((is_sorted(cur) == 1))
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

static	int	check_key(char *key, char *value, t_env **head)
{
	t_env *tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	env_add(char *new_var, t_env **env)
{
	t_env	*new_node;
	char	**tmp;
	int		i;
	
	i = 0;
	tmp = ft_split_export(new_var, '=');
	if(!(new_node = malloc(sizeof(t_env))))
		return(1);
	while (tmp[0][i])
	{
		if (tmp[0][i] == '+')
			tmp[0][i] = '\0';
		i++;
	}
	if(check_key(tmp[0], tmp[1], env) == 0)
	{
		new_node->key = tmp[0];
		new_node->value = tmp[1];	
		new_node->status = 0;
		ft_lstadd_back(env, new_node);
	}
	return (0);
}

int	ft_export(char **cmd, t_env **env)
{
	int i;
	char	**tmp;

	i = 1;
	if (!cmd[i] && print_declare((*env)))
		return (0);
	while (cmd[i])
	{
		tmp = ft_split_export(cmd[i], '=');
		if (valid_key(tmp[0]) == 1)
			return (1);
		if (add_check(tmp[0], tmp[1], env) == 0)
			env_add(cmd[i], env);
		free_str(tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}