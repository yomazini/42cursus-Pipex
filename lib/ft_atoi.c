/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:17:54 by ymazini           #+#    #+#             */
/*   Updated: 2024/11/12 23:46:01 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return (i);
}

static int	ft_get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	ft_add_digit(long long *result, char digit, int sign)
{
	long long	temp;

	temp = *result;
	*result = *result * 10 + (digit - '0');
	if (*result / 10 != temp)
	{
		if (sign == 1)
			return (-1);
		if (sign == -1)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	int			check;

	i = ft_skip_whitespace(str);
	sign = ft_get_sign(str, &i);
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = ft_add_digit(&result, str[i], sign);
		if (check != 1)
			return (check);
		i++;
	}
	return (sign * result);
}
