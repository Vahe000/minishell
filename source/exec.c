/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:10:51 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 20:11:10 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mankapartez(t_main *node, char **new_env, char *cmd)
{
	rl_catch_signals = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (node->cmd[0])
	{
		if (!if_built_in(node->cmd[0]))
		{
			if (node->cmd[0][0] == '/' || node->cmd[0][0] == '.')
			{
				if (execve(node->cmd[0], node->cmd, new_env) == -1)
					cnf_error(node->cmd[0]);
			}
			else
			{
				if (execve(cmd, node->cmd, new_env) == -1)
					cnf_error(node->cmd[0]);
			}
		}
	}
	exit(1);
}

int	ft_manushak(t_main **node, t_env **data, char **cmd)
{
	char	*piz;
	int		ret;
	char	*ret_dup;

	ret = -1;
	ret_dup = 0;
	if ((*node)->cmd[0])
	{
		ret = builtin(node, data);
		ret_dup = ft_itoa(ret);
		check_key("?", ret_dup, data);
		(*data)->exit_status = ret;
		free(ret_dup);
		ret_dup = 0;
		piz = ft_strdup((*node)->cmd[0]);
		*cmd = cmd_to_acc(&piz, data);
	}
	return (ret);
}

void	ft_else_mankapartez(t_env **envv)
{
	int		ret;
	char	*ret_dup;

	wait(&ret);
	{
		if (WIFSIGNALED(ret) != 0)
		{
			ret_dup = ft_itoa(WTERMSIG(ret) + 128);
			(*envv)->exit_status = WTERMSIG(ret) + 128;
			check_key("?", ret_dup, envv);
			free(ret_dup);
			ret_dup = 0;
		}
		else if (WIFEXITED(ret))
		{
			ret_dup = ft_itoa(WEXITSTATUS(ret));
			(*envv)->exit_status = WEXITSTATUS(ret);
			check_key("?", ret_dup, envv);
			free(ret_dup);
			ret_dup = 0;
		}
	}
}

static void	ft_du_free(char **new_env, char *cmd)
{
	free_arr(new_env);
	ft_free_tox(cmd);
}

int	execve_part(t_main *node, t_env **data)
{
	pid_t	pid;
	char	*cmd;
	char	**new_env;

	cmd = NULL;
	new_env = list_to_env(*data);
	do_redir(node);
	node->m_flag = ft_manushak(&node, data, &cmd);
	if (node->c_flag == 777)
	{
		ft_du_free(new_env, cmd);
		return ((node->c_flag = 0));
	}
	if (cmd != NULL && node->m_flag == -1 && node->infile_status != -1)
	{
		pid = fork();
		if (pid == 0)
			ft_mankapartez(node, new_env, cmd);
		else
			ft_else_mankapartez(data);
		signal(SIGINT, &handler);
		signal(SIGQUIT, SIG_IGN);
	}
	ft_du_free(new_env, cmd);
	return (0);
}
