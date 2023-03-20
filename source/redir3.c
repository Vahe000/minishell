/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:42:25 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/31 18:03:44 by vasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_heredoc(t_main *node)
{
	int	i;

	i = -1;
	if (*node->heredoc)
	{
		while (node->heredoc[++i])
		{
			if (i == arr_len(node->heredoc) - 1)
				heredoc_redirect(node->heredoc[i], &node);
			else
				heredoc_no_redirect(node->heredoc[i]);
		}
	}
}

void	do_infile(t_main *node)
{
	int	i;

	i = -1;
	if (*node->infile)
	{
		while (node->infile[++i])
		{
			if (i == arr_len(node->infile) - 1)
				infile_redir(node->infile[i], node);
			else
				infile_no_redir(node->infile[i], node);
		}
	}
}

void	do_outfile(t_main *node)
{
	int	i;

	i = -1;
	if (*node->outfile)
	{
		while (node->outfile[++i])
		{
			if (i == arr_len(node->outfile) - 1)
				outfile(node->outfile[i]);
			else
				no_outfile(node->outfile[i]);
		}
	}
}

void	do_append(t_main *node)
{
	int	i;

	i = -1;
	if (*node->append)
	{
		while (node->append[++i])
		{
			if (i == arr_len(node->append) - 1)
				append_redir(node->append[i]);
			else
				append_no_redir(node->append[i]);
		}
	}
}

void	do_redir(t_main *node)
{
	node->infile_status = 0;
	node->infile_error = 0;
	do_heredoc(node);
	do_infile(node);
	do_outfile(node);
	do_append(node);
}
