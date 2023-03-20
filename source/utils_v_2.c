/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_v_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leyeghia <leyeghia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:59:54 by vasargsy          #+#    #+#             */
/*   Updated: 2023/01/28 12:24:58 by leyeghia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst || !lst->next)
		return (0);
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

long	ft_atoi(const char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			b *= -1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		a = a * 10 + *str - '0';
		str++;
	}
	return ((unsigned long)a * b);
}

static size_t	str_len(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	nn;	

	nn = n;
	len = str_len(nn);
	str = malloc(len + 1);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (nn < 0)
	{
		nn *= -1;
		str[0] = '-';
	}
	str[len] = 0;
	while (nn)
	{
		str[(len--) - 1] = ((nn % 10) + 48);
		nn /= 10;
	}
	return (str);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] == '0')
		i++;
	i = ft_strlen(str);
	if (i > 18)
	{
		if (str[i - 1] == '8' || str[i - 1] == '9')
			return (0);
	}
	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}
