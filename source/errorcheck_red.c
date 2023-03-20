/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorcheck_red.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:57:24 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/21 22:41:02 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_red1(char **matrix)
{
	int	i;

	i = -1;
	while (matrix && matrix[++i])
	{
		if (ft_strlen(matrix[i]) < 2)
			return (1);
	}
	return (0);
}

int	check_red2(char **matrix)
{
	int	i;

	i = -1;
	while (matrix && matrix[++i])
	{
		if (ft_strlen(matrix[i]) < 3)
			return (1);
	}
	return (0);
}

int	unexpected_error1(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (ft_quote_ignore(&str, &i))
			break ;
		if (str[i] == '<')
		{
			if (str[i + 1] == '>' || (str[i + 1] == '<' && str[i + 2] == '>'))
			{
				ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
				return (1);
			}
			else if (str[i + 1] == '<')
			{
				if (str[i + 2] == '<')
				{
					ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	unexpected_error2(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (ft_quote_ignore(&str, &i))
			break ;
		if (str[i] == '>')
		{
			if (str[i + 1] == '<' || (str[i + 1] == '>' && str[i + 2] == '<'))
			{
				ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
				return (1);
			}
			else if (str[i + 1] == '>')
			{
				if (str[i + 2] == '>')
				{
					ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	errorcheck_red(t_main **head, t_env **envv, char *line)
{
	t_main	*data;

	data = *head;
	if (unexpected_error1(data->read_line)
		|| unexpected_error2(data->read_line))
	{
		check_key("?", "258", envv);
		pars_free(head, &line);
		return (1);
	}
	if (check_red1(data->infile) || check_red1(data->outfile)
		|| check_red2(data->heredoc) || check_red2(data->append))
	{
		check_key("?", "258", envv);
		write(2, "syntax error near unexpected token `newline'\n", 45);
		pars_free(head, &line);
		return (1);
	}
	return (0);
}
