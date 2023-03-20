/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcheck_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:07:51 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/31 14:16:12 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_error(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '|')
		{
			++i;
			while (str && str[i] == ' ')
				++i;
			if (str[i] == '|')
				return (1);
		}
		if (str[i] == '\0')
			break ;
		++i;
	}
	return (0);
}

int	error_pipe(char *str, int tokens_count, t_env **envv)
{
	int	i;
	int	pipe_count;

	pipe_count = 0;
	i = -1;
	while (str && str[++i])
	{
		ft_quote_ignore(&str, &i);
		if (str[i] == '|')
			++pipe_count;
		if (!str[i])
			break ;
	}
	if (pipe_count != tokens_count - 1 || if_error(str))
	{
		check_key("?", "258", envv);
		write(2, "syntax error near unexpected token `|'\n", 39);
		return (1);
	}
	return (0);
}
