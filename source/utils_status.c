/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:57:25 by leyeghia          #+#    #+#             */
/*   Updated: 2023/02/01 14:34:46 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fd_dup_close(t_main *head, int size, int (*fd)[2])
{
	int	i;

	i = -1;
	if (head->index == 0)
		dup2(fd[0][1], 1);
	else if ((head->index == size - 1) && *head->heredoc)
		dup2(fd[head->index][0], 0);
	else if (head->index == size - 1)
		dup2(fd[head->index - 1][0], 0);
	else
	{
		if ((head->index == size - 1)
			&& *head->heredoc)
			dup2(fd[head->index][0], 0);
		else
			dup2(fd[head->index - 1][0], 0);
		dup2(fd[head->index][1], 1);
	}
	while (++i < size - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

int	ft_non_valid(char **cmd)
{
	int		i;
	char	**tmp;

	i = 1;
	while (cmd[i])
	{
		tmp = ft_split_export(cmd[i], '=');
		if (valid_key(tmp[0]) == 1)
			return (1);
		free_arr(tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}

void	ft_exec_pipe(t_main *head, t_env **envv)
{
	char	*piz;
	char	*cmd;
	int		exit_status;

	exit_status = 0;
	cmd = NULL;
	piz = NULL;
	piz = ft_strdup(head->cmd[0]);
	cmd = cmd_to_acc(&piz, envv);
	free(piz);
	piz = NULL;
	if (execve(cmd, head->cmd, list_to_env(*envv)) == -1)
	{
		if (!if_built_in(head->cmd[0]))
			cnf_error(head->cmd[0]);
		else if (if_built_in(head->cmd[0]))
			exit(ft_exit(head->cmd, *envv, 1));
	}
	free(cmd);
	cmd = NULL;
	exit(0);
}

void	ft_close_fd(int size, int (*fd)[2])
{
	int	i;

	i = -1;
	while (++i < size - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	ft_statuses(t_env **envv, int *pid, int size)
{
	int		i;
	int		ret;
	char	*ret_dup;

	ret_dup = NULL;
	i = -1;
	while (++i < size)
	{
		waitpid(pid[i], &ret, 0);
		if (WIFSIGNALED(ret) != 0)
		{
			ret_dup = ft_itoa(WTERMSIG(ret) + 128);
			(*envv)->exit_status = WTERMSIG(ret) + 128;
			check_key("?", ret_dup, envv);
			ft_free_tox(ret_dup);
			g_exit_status = 0;
		}
		else if (WIFEXITED(ret))
		{
			ret_dup = ft_itoa(WEXITSTATUS(ret));
			(*envv)->exit_status = WEXITSTATUS(ret);
			check_key("?", ret_dup, envv);
			ft_free_tox(ret_dup);
		}
	}
}
