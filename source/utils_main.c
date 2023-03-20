/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:49:47 by leyeghia          #+#    #+#             */
/*   Updated: 2023/02/01 15:15:39 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_main *head, t_env **envv, int in_cpy, int out_cpy)
{
	head->lst_size = list_size(head);
	if (head->lst_size == 1)
		execve_part(head, envv);
	else
		ft_pipe(head, envv, head->lst_size);
	dup2(in_cpy, 0);
	dup2(out_cpy, 1);
}

void	ft_sig_dup(t_main *head, t_env **envv, int size, int (*fd)[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_fd_dup_close(head, size, fd);
	ft_exec_pipe(head, envv);
}

void	ft_close_free(int size, int (*fd)[2], t_env **envv, int *pid)
{
	ft_statuses(envv, pid, size);
	free(pid);
	free(fd);
}

struct s_helps
{
	int		(*fd)[2];
	int		*pid;
	int		in_cpy;
	int		outcpy;
	int		i;
};

void	ft_pipe(t_main *head, t_env **envv, int size)
{
	struct s_helps	help;

	help.in_cpy = dup(0);
	help.outcpy = dup(1);
	help.i = -1;
	help.fd = malloc(sizeof(*help.fd) * (size - 1));
	while (++help.i < size - 1)
		pipe(help.fd[help.i]);
	help.pid = malloc(sizeof(int) * size);
	help.i = 0;
	while (head)
	{
		do_redir(head);
		help.pid[help.i] = fork();
		if (ft_fork(help.pid, envv, help.i) == 42)
			break ;
		else if (help.pid[help.i] == 0)
			ft_sig_dup(head, envv, size, help.fd);
		help.i++;
		head = head->next;
		dup2(help.in_cpy, 0);
		dup2(help.outcpy, 1);
	}
	ft_close_fd(size, help.fd);
	ft_close_free(size, help.fd, envv, help.pid);
}
