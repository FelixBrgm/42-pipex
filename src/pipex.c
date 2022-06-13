/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:49:30 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/12 23:14:31 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main_childs(t_child **childs, char **env);

int	main(int argc, char **argv, char **env)
{
	t_child	**childs;

	if (argc != 5)
	{
		ft_printf("wrong number of arguments");
		return (1);
	}
	close(open(argv[argc -1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR));
	childs = input_parse(argc, argv, env);
	if (main_childs(childs, env))
		return (1);
	waitpid(0, NULL, 0);
	return (0);
}

int	main_childs(t_child **childs, char **env)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
		child_first(childs[0], env, fd);
	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
		child_last(childs[1], env, fd, 0);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
