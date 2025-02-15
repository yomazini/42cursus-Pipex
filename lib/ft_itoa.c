/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:08:17 by ymazini           #+#    #+#             */
/*   Updated: 2024/11/13 14:06:22 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long c)
{
	int	i;

	i = 0;
	if (c <= 0)
	{
		i++;
		c = -c;
	}
	while (c)
	{
		c /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	c;
	char	*str;
	int		len;

	c = n;
	len = int_len(c);
	str = (char *)malloc (len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (c == 0)
		str[0] = '0';
	if (c < 0)
	{
		str[0] = '-';
		c = -c ;
	}
	while (c)
	{
		str[len--] = (c % 10) + '0';
		c /= 10;
	}
	return (str);
}
