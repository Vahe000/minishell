/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:01:50 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/25 16:32:31 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_value(char *key, t_env *head)
{
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
			return (head->value);
		head = head->next;
	}
	return (0);
}

static void	update_oldpwd(t_env *env)
{
	char	cwd[1024];
	char	*old_pwd;

	getcwd(cwd, 1024);
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (check_value(old_pwd, env) == 0)
		env_add(old_pwd, &env);
	free(old_pwd);
}

int	ft_cd(char **cmd, t_env **data)
{
	update_oldpwd(*data);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		if (chdir(check_value("HOME", *data)) == 0)
			return (0);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (1);
		}	
	}
	else
	{
		if (chdir(cmd[1]) == 0)
			return (0);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}
