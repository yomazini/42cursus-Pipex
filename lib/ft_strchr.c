/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:54:24 by ymazini           #+#    #+#             */
/*   Updated: 2024/11/12 23:57:33 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	int		i;

	chr = (char) c;
	i = -1;
	while (s[++i])
	{
		if (s[i] == chr)
			return ((char *)&s[i]);
	}
	if (s[i] == chr)
		return ((char *)&s[i]);
	return (NULL);
}
