/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 12:06:49 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/11 12:18:41 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_first(t_input *input, char** env, int fd[2])
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	input->cmd1 = ft_strjoin(input->cmd1, " ");
	input->cmd1 = ft_strjoin(input->cmd1, input->file1);
	execve(input->cmd1_dst, ft_split(input->cmd1, ' '),env);
}

void	child_last(t_input *input, char** env, int fd[2])
{
	fclose(fopen(input->file2, "w"));
	int fdd = open(input->file2, O_RDWR);
	dup2(fd[0], STDIN_FILENO);
	dup2(fdd, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fdd);
	execve(input->cmd2_dst, ft_split(input->cmd2, ' '),env);
}

void	child_betweeen()
{
	
}