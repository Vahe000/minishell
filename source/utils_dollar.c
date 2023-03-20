/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:05:24 by leyeghia          #+#    #+#             */
/*   Updated: 2023/01/24 12:15:56 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dollar_here(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (0);
		++i;
	}
	return (1);
}

char	*checking_key_dollar(char *key, t_env **head, t_main *data)
{
	char	*value;
	t_env	*tmp;

	tmp = *head;
	value = 0;
	(void) data;
	while (*head)
	{
		if (ft_strcmp(key, (*head)->key) == 0)
		{
			value = ft_strdup((*head)->value);
			*head = tmp;
			return (value);
		}
		*head = (*head)->next;
	}
	*head = tmp;
	return (0);
}

int	ft_len_for_dollar(t_main **head, int i, int j)
{
	int	len;

	len = 0;
	while ((*head)->cmd && (*head)->cmd[i] && (*head)->cmd[i][j + len] &&
			!ft_strchr(METACHARS, (*head)->cmd[i][j + len])
			&& (*head)->cmd[i][j + len] != '"'
			&& (*head)->cmd[i][j + len] != '\'')
	{
		++len;
		if ((*head)->cmd[i][j + len] == '$')
			break ;
	}
	return (len);
}

void	ft_check_for_change(t_main **data, t_env **ennv, int i, int j)
{	
	int		len;
	char	*str;
	char	*strrrr;
	char	*str0;

	str = NULL;
	str0 = NULL;
	strrrr = NULL;
	len = ft_len_for_dollar(data, i, j);
	str = ft_substr((*data)->cmd[i], 1 + j, len - 1);
	strrrr = ft_strdup((*data)->cmd[i]);
	if ((*data)->cmd[i])
		free((*data)->cmd[i]);
	str0 = checking_key_dollar(str, ennv, *data);
	(*data)->cmd[i] = ft_change_dollar(strrrr, str, str0, j);
	free(str0);
	free(str);
	free(strrrr);
	str = 0;
	str0 = 0;
	strrrr = 0;
}

char	*ft_change_dollar(char *src, char *oldstr, char *newstr, int start)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	ret = malloc(ft_strlen(src) + ft_strlen(newstr) - ft_strlen(oldstr) + 1);
	if (!ret)
		return (0);
	while (src && src[j])
	{
		if (i == start)
		{
			while (newstr && newstr[k])
				ret[i++] = newstr[k++];
			j += ft_strlen(oldstr) + 1;
		}
		if (src[j] == '\0')
			break ;
		ret[i++] = src[j++];
	}
	ret[i] = '\0';
	return (ret);
}
