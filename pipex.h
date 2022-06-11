/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:15:19 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/11 12:18:51 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libs/libs.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_input
{
	char	*cmd1;
	char	*cmd2;
	char	*cmd1_dst;
	char	*cmd2_dst;
	char	*file1;
	char	*file2;
}				t_input;

typedef struct s_exec
{
	char	*cmd;
	char	*dst;
}				t_exec;
// Children
void	child_first(t_input *input, char** env, int fd[2]);
void	child_last(t_input *input, char** env, int fd[2]);



#endif
