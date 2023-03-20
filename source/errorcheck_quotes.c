/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcheck_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:22:32 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/21 22:39:16 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote_count(char *str, int *index, char c)
{
	int	count;

	count = 1;
	while (str && str[++*index] && str[*index] != c)
		;
	if (str[*index] == c)
		++count;
	return (count);
}

int	error_quote(char *str, t_env **envv)
{
	int	i;
	int	count_single_q;
	int	count_double_q;

	count_single_q = 0;
	count_double_q = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] && str[i] == '"')
			count_double_q += ft_check_quote_count(str, &i, '"');
		else if (str[i] && str[i] == '\'')
			count_single_q += ft_check_quote_count(str, &i, '\'');
		if (!str[i])
			break ;
	}
	if (count_double_q % 2 == 1 || count_single_q % 2 == 1)
	{
		check_key("?", "258", envv);
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (1);
	}
	return (0);
}
