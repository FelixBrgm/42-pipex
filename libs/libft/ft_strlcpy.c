/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:42:15 by fbruggem          #+#    #+#             */
/*   Updated: 2022/03/31 13:52:35 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	while (*src != '\0')
	{
		if (i + 1 < (int) dstsize)
		{
			*dst = *src;
			dst++;
		}
		src++;
		i++;
	}
	if (dstsize)
		*dst = '\0';
	return (i);
}
