/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:15:19 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/12 23:18:01 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libs/libs.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_child
{
	char	*cmd;
	char	*dst;
	char	*file;
}				t_child;

// Children
void	child_first(t_child *child, char **env, int fd[2]);
void	child_last(t_child *child, char **env, int fd[2], int here_doc_res);
void	child_between(t_child *child, char **env,
			int fd_before[2], int fd_after[2]);

// Where
char	*where(char **env, char *cmd);

// Input
t_child	**input_parse(int argc, char **argv, char **env);
void	input_error(char **err);

// Here_doc
int		here_doc(int *argc, char **argv);

// Utils
void	close_fd(int fd[2]);
void	copy_fd(int *fd_src[2], int *fd_dst[2]);
void	free_childs(t_child **childs);

#endif