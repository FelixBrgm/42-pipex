/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:51:06 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/13 01:06:57 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	input_check(char **argv, char **env);

t_child	**input_parse(int argc, char **argv, char **env)
{
	t_child	**childs;
	int		i;
	char	**temp;

	input_check(argv, env);
	argv++;
	argc--;
	childs = ft_calloc(argc - 1, sizeof(t_child *));
	i = 1;
	while (i < argc -1)
	{
		childs[i -1] = ft_calloc(1, sizeof(t_child));
		childs[i -1]->cmd = argv[i];
		i++;
	}
	childs[0]->file = argv[0];
	childs[argc -3]->file = argv[argc -1];
	i = 0;
	while (childs[i])
	{
		temp = ft_split(childs[i]->cmd, ' ');
		childs[i++]->dst = where(env, temp[0]);
		ft_free_split(temp);
	}
	return (childs);
}

void	input_check(char **argv, char **env)
{
	int		i;
	char	*error;
	char	**temp;
	char	*temp_dest;

	error = NULL;
	i = 1;
	while (argv[i + 1])
	{
		if (i == 1 && ft_fileexists(argv[i]))
				error = ft_strjoin_free(error,
					ft_strjoin("|no such file or directory: ", argv[i]));
		else if (i != 1)
		{
			temp = ft_split(argv[i], ' ');
			temp_dest = where(env, temp[0]);
			if (!temp_dest)
			error = ft_strjoin_free(error, ft_strjoin("|command not found: ",
							ft_split(argv[i], ' ')[0]));
			free(temp_dest);
			ft_free_split(temp);
		}
		i++;
	}
	input_error(ft_split(error, '|'));
}

void	input_error(char **err)
{
	int	i;

	i = 0;
	if (err)
	{
		while (err[i])
		{
			ft_printf("%s\n", err[i]);
			i++;
		}
		ft_free_split(err);
	}
}
