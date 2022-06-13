/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 10:36:00 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/13 00:56:28 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_first(t_child *child, char **env, int fd[2])
{
	int	fd_in;

	fd_in = open(child->file, O_RDONLY);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(child->dst, ft_split(child->cmd, ' '), env);
	exit (1);
}

void	child_last(t_child *child, char **env, int fd[2], int here_doc)
{
	int	fd_out;

	if (here_doc)
	{
		fd_out = open(child->file, O_APPEND | O_WRONLY);
		if (fd_out < 0)
			open(child->file, O_CREAT, S_IRUSR | S_IWUSR);
	}
	else
		fd_out = open(child->file, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRUSR | S_IWUSR);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_out);
	execve(child->dst, ft_split(child->cmd, ' '), env);
	exit (1);
}

void	child_between(t_child *child, char **env,
			int fd_before[2], int fd_after[2])
{
	dup2(fd_before[0], STDIN_FILENO);
	dup2(fd_after[1], STDOUT_FILENO);
	close(fd_before[0]);
	close(fd_before[1]);
	execve(child->dst, ft_split(child->cmd, ' '), env);
	exit (1);
}
