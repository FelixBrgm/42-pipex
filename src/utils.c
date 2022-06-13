/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:34:27 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/12 22:38:13 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	copy_fd(int *fd_src[2], int *fd_dst[2])
{
	fd_dst[0] = fd_src[0];
	fd_dst[1] = fd_src[1];
}

void	free_childs(t_child **childs)
{
	int	i;

	i = 0;
	while (childs[i])
	{
		free(childs[i]->dst);
		free(childs[i]);
		i++;
	}
	free(childs);
}
