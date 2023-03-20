/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:37:55 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/26 16:17:26 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_free_access(char **str, char **ret_str, char ***path)
{
	char	*s;
	int		i;

	i = -1;
	while ((*path)[++i])
	{
		s = ft_strjoin((*path)[i], *str);
		if (access(s, 0) == 0)
		{
			free(*str);
			free_arr(*path);
			ft_free_tox(*ret_str);
			return (s);
		}
		free(s);
	}
	return (0);
}

char	*cmd_to_acc(char **cmd, t_env **data)
{
	char	**path;
	char	*str;
	char	*ret_str;
	char	*ret_str0;

	path = path_find(*data);
	ret_str = ft_strdup(*cmd);
	free(*cmd);
	*cmd = 0;
	if (!path)
		return (ret_str);
	str = ft_strjoin("/", ret_str);
	ret_str0 = ft_free_access(&str, &ret_str, &path);
	if (ret_str0)
		return (ret_str0);
	free(str);
	free_arr(path);
	return (ret_str);
}

char	**path_find(t_env *data)
{
	char	**value;
	t_env	*cur;

	cur = data;
	value = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, "PATH") == 0)
		{
			value = ft_split(cur->value, ':');
			break ;
		}
		cur = cur->next;
	}
	return (value);
}

int	if_built_in(char *str)
{
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "echo") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, "<") || !ft_strcmp(str, ">>")
		|| !ft_strcmp(str, "<<"))
		return (1);
	else
		return (0);
}

int	builtin(t_main **data, t_env **env)
{
	if (!ft_strcmp((*data)->cmd[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp((*data)->cmd[0], "env"))
		return (ft_env(*env));
	else if (!ft_strcmp((*data)->cmd[0], "echo"))
		return (ft_echo((*data)));
	else if (!ft_strcmp((*data)->cmd[0], "exit"))
		return (ft_exit((*data)->cmd, *env, 0));
	else if (!ft_strcmp((*data)->cmd[0], "unset"))
		return (ft_unset((*data)->cmd, env));
	else if (!ft_strcmp((*data)->cmd[0], "export"))
		return (ft_export((*data)->cmd, env));
	else if (!ft_strcmp((*data)->cmd[0], "cd"))
		return (ft_cd((*data)->cmd, env));
	else
		return (-1);
}
