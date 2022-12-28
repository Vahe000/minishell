/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:10:51 by vasargsy          #+#    #+#             */
/*   Updated: 2022/12/28 17:58:49 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **path_find(t_env *data)
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

char	*cmd_to_acc(char **cmd, t_env **data)
{
	char	**path;
	char	*str;
	char	*s;
	int		i;

	i = -1;
	printf("%s\n", cmd[0]);
	path = path_find(*data);
	while (path[++i])
	{
		str = ft_strjoin("/", cmd[0]);
		printf("%d\n", __LINE__);
		s = ft_strjoin(path[i], str);
		if (access(s, 0) == 0)
			return (s);
	}
	return (0);
}

// int	execve_part(t_main *node, t_env *data)
// {
// 	char	*str;

// 	str = cmd_to_acc(node->cmd[])
// }

void	builtin(t_main **data, t_env **env)
{
	if(!(*data)->cmd || !(*data)->cmd[0])
		return ;
	if (!ft_strcmp((*data)->cmd[0], "/pwd"))
		ft_pwd();
	if (!ft_strcmp((*data)->cmd[0], "/env"))
		ft_env(env);
	if (!ft_strcmp((*data)->cmd[0], "/echo"))
		ft_echo(*data);
	if (!ft_strcmp((*data)->cmd[0], "/exit"))// petq a anel der
		exit(0);
	if (!ft_strcmp((*data)->cmd[0], "/unset"))
		ft_unset((*data)->cmd, env);
	if (!ft_strcmp((*data)->cmd[0], "/export"))
		ft_export((*data)->cmd, env);
	if (!ft_strcmp((*data)->cmd[0], "/cd"))
		ft_cd((*data)->cmd, env);
	if (!ft_strncmp((*data)->cmd[0], "/<<", 2))//der ban petq a arvi erevi
		heredoc_redir((*data)->cmd[0]);
	if (!ft_strncmp((*data)->cmd[0], "/>", 2))
		infile_redir((*data)->cmd[0]);
}
