/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:36:29 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/09 16:13:35 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*mem;
	int		i;

	i = 0;
	mem = ft_calloc(1, ft_strlen(s1) + 1);
	if (!mem)
		return (NULL);
	while (s1[i] != '\0')
	{	
		mem[i] = s1[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
