/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:26:06 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/31 14:14:06 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pid_kill(int i, int *pid, t_env **envv)
{
	while (--i >= 0)
	{
		kill(pid[i], SIGKILL);
		waitpid(pid[i], NULL, WUNTRACED);
	}
	ft_putstr_fd("fork error\n", 2);
	check_key("?", "1", envv);
}

int	ft_fork(int	*pid, t_env **envv, int i)
{
	if (pid[i] == -1)
	{
		ft_pid_kill(i, pid, envv);
		return (42);
	}
	return (0);
}

void	append_no_redir(char *file)
{
	int	fd;

	file += 2;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	close(fd);
}

void	ft_control_c(t_env	**env)
{
	if (g_exit_status == 26354)
	{
		g_exit_status = 0;
		check_key("?", "1", env);
	}
}
