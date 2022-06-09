/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:33:44 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/09 17:06:25 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
char	*get_cmd_dst(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*res;
	char	*temp;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	paths = ft_split(&env[i][5],':');
	i = 0;
	while (paths[i])
	{
		temp = paths[i];
		temp = ft_strjoin(temp,"/");
		res = ft_strjoin(temp,cmd);
		free(temp);
		if (access(res, 0) == 0)
		{
			i = 0;
			ft_free_split(paths);
			return (res);
		}
		free(res);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int main(int argc, char **argv, char** env)
{
	t_input	input;
	
	if (argc != 5)
		return (1);
	// INPUT HANDLING
	// INPUT PARSING
		
	input.file1 = argv[1];
	input.file2 = argv[4];
	input.cmd1 = argv[2];
	input.cmd2 = argv[3];
	char **temp = ft_split(input.cmd1, ' ');
	input.cmd1_dst = get_cmd_dst(env, temp[0]);
	ft_free_split(temp);
	temp = ft_split(input.cmd2, ' ');
	input.cmd2_dst = get_cmd_dst(env, temp[0]);
	ft_free_split(temp);
	// Creating the sub processis
	int	fd[2];
	int	id;
	if (pipe(fd) == -1)
		return (1);

	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		input.cmd1 = ft_strjoin(input.cmd1, " ");
		input.cmd1 = ft_strjoin(input.cmd1, input.file1);
		execve(input.cmd1_dst, ft_split(input.cmd1, ' '),env);
	}
	ft_printf("SRC: %s\n", input.file2);
	int fdd = open(input.file2, O_RDWR);
	dup2(fd[0], STDIN_FILENO);
	dup2(fdd, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fdd);
	waitpid(0, NULL, 0);
	execve(input.cmd2_dst, ft_split(input.cmd2, ' '),env);
	return (0);
}