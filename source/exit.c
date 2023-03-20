/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:35:40 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/31 19:18:35 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_abs(int i)
{
	if (i < 0)
		return (i * -1);
	else
		return (i);
}

void	prnt_exit_error(void)
{
	ft_putstr_fd("exit\nexit code must be numeric\n", 2);
	exit(255);
}

void	cnt_2(int num, int flag)
{
	if (num >= 0)
	{
		if (flag == 0)
			ft_putstr_fd("exit\n", 2);
		exit(num % 256);
	}
	else
	{
		if (flag == 0)
			ft_putstr_fd("exit\n", 2);
		exit(256 - ft_abs(num) % 256);
	}
}

int	arr_len(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
		;
	return (i);
}

int	ft_exit(char **cmd, t_env *env, int flag)
{
	if (!cmd[1])
		exit(env->exit_status);
	if (arr_len(cmd) > 2)
	{
		if (is_digit(cmd[1]))
			exit_to_many(env);
		else
			prnt_exit_error();
		return (1);
	}
	else if (flag == 0 || flag == 1)
	{
		if (is_digit(cmd[1]) && (ft_atoi(cmd[1]) > INT_MAX
				|| ft_atoi(cmd[1]) < INT_MIN))
			prnt_exit_error();
		else if (!is_digit(cmd[1]))
			prnt_exit_error();
		else
		{
			cnt_2(ft_atoi(cmd[1]), flag);
			return (1);
		}
	}
	return (0);
}
