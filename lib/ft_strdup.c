/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:04:58 by ymazini           #+#    #+#             */
/*   Updated: 2024/11/21 18:25:57 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	size;
	char	*str;

	size = ft_strlen(src);
	str = malloc (size + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, src, size);
	str [size] = '\0';
	return (str);
}
