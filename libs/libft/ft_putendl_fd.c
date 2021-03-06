/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:32:08 by fbruggem          #+#    #+#             */
/*   Updated: 2022/03/31 14:12:08 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	a;

	if (s != NULL)
	{
		a = '\n';
		while (*s != '\0')
		{
			write(fd, s, 1);
			s++;
		}
		write(fd, &a, 1);
	}
}
