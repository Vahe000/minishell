/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:48:27 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 14:46:39 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	dghonyan(void)
{
	return (0);
}

void	handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_done = 1;
	g_exit_status = 26354;
}

int	main(int argc, char **argv, char **envp)
{
	t_merge			merge;
	struct termios	inch;

	winter_is_comming(envp, &merge.v_env, argc, argv);
	rl_catch_signals = 0;
	rl_event_hook = dghonyan;
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
	merge.in_cpy = dup(0);
	merge.out_cpy = dup(1);
	tcgetattr(0, &inch);
	while (1)
	{
		tcsetattr(0, 0, &inch);
		merge.l_head = NULL;
		if (ft_start_main(&merge.v_env, &merge.line))
			continue ;
		if (lexer(&merge.l_head, merge.line, merge.v_env))
			continue ;
		if (parser(&merge.l_head, &merge.v_env, merge.line))
			continue ;
		execution(merge.l_head, &merge.v_env, merge.in_cpy, merge.out_cpy);
		pars_free(&merge.l_head, &merge.line);
	}
	return (0);
}
