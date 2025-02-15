/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:48:23 by ymazini           #+#    #+#             */
/*   Updated: 2024/11/12 23:50:55 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	long	nmr;
	char	str[12];

	if (fd < 0)
		return ;
	nmr = n;
	i = 0;
	if (nmr == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (nmr < 0)
	{
		nmr = -nmr;
		ft_putchar_fd('-', fd);
	}
	while (nmr)
	{
		str[i++] = nmr % 10 + '0';
		nmr /= 10;
	}
	while (i-- > 0)
		ft_putchar_fd(str[i], fd);
}
