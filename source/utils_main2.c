/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:57:14 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/28 17:45:46 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_exit(void)
{
	printf("exit\n");
	exit(0);
}

void	winter_is_comming(char **envp, t_env **envv, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	*envv = NULL;
	env_to_list(envv, envp);
	(*envv)->exit_status = 0;
	env_add_item("?", "0", envv);
	change_shlvl((*envv));
	printf(GRN"wellcome! \n"CYN);
}

void	exit_to_many(t_env *env)
{
	ft_putstr_fd("exit\nto many arguments\n", 2);
	check_key("?", "1", &env);
}

int	ft_start_main(t_env **envv, char **line)
{
	*line = readline("minishell> ");
	ft_control_c(envv);
	if (*line == 0)
		ft_print_exit();
	if (*line[0])
	{
		add_history(*line);
		return (0);
	}
	else
	{
		ft_free_tox(*line);
		return (1);
	}
}
