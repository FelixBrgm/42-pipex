/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:33:44 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/11 12:57:33 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_cmd_dst(char **env, char *cmd);
t_input	*input_parse(int argc, char **argv, char **env);
void	input_check(int argc, char**argv, char **env);
void	input_error(char **err);

int main(int argc, char **argv, char** env)
{
	t_input	*input;
	
	input = input_parse(argc, argv, env);
	if (!input)
		return (1);

	int	fd[2];
	int	id;
	if (pipe(fd) == -1)
		return (1);

	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
		child_first(input, env, fd);
	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
		child_last(input, env, fd);
	waitpid(0, NULL, 0);
	return (0);
}

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

t_input *input_parse(int argc, char **argv, char **env)
{
	t_input	*input;
	char	**temp;

	input_check(argc, argv, env);
	input = ft_calloc(1, sizeof(*input));
	if (!input)
		return (NULL);
	input->file1 = argv[1];
	input->file2 = argv[4];
	input->cmd1 = argv[2];
	input->cmd2 = argv[3];
	temp = ft_split(input->cmd1, ' ');
	input->cmd1_dst = get_cmd_dst(env, temp[0]);
	ft_free_split(temp);
	temp = ft_split(input->cmd2, ' ');
	input->cmd2_dst = get_cmd_dst(env, temp[0]);
	ft_free_split(temp);
	return (input);
}

void	input_check(int argc, char**argv, char **env)
{
	//// LEAKKSKSKSKKSKS
	char	**temp;
	char	*temp_dest;
	char	*error;

	error = NULL;
	if (argc != 5)
		input_error(ft_split("wrong number of arguments", 'x'));
	if(ft_fileexists(argv[1]))
		error = ft_strjoin_free(error, ft_strjoin("|no such file or directory: ", argv[1]));
	temp = ft_split(argv[2], ' ');
	temp_dest = get_cmd_dst(env, temp[0]);
	if (!temp_dest)
		error = ft_strjoin_free(error, ft_strjoin("|command not found: ", ft_split(argv[2], ' ')[0]));
	free(temp_dest);
	ft_free_split(temp);
	temp = ft_split(argv[3], ' ');
	temp_dest = get_cmd_dst(env, temp[0]);
	if (!temp_dest)
		error = ft_strjoin_free(error, ft_strjoin("|command not found: ", ft_split(argv[3], ' ')[0]));
	free(temp_dest);
	ft_free_split(temp);	
	if (error)
		input_error(ft_split(error, '|'));
}
void	input_error(char **err)
{
	int	i;

	i = 0;
	while (err[i])
	{
		ft_printf("%s\n",err[i]);
		i++;
	}
	ft_free_split(err);
	exit (1);
}