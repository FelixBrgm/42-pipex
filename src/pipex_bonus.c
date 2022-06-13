/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:13:59 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/13 00:46:20 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

typedef struct s_vars
{
	int		i;
	int		here_doc_res;
	int		id;
	t_child	**childs;
}				t_vars;

typedef struct s_fds
{
	int	before[2];
	int	after[2];
}				t_fds;

void	main_child(char **env, t_fds *fds, t_vars vars);
void	main_iter(char **env, int here_doc_res, t_child **childs, t_fds *fds);

int	main(int argc, char **argv, char **env)
{
	t_child	**childs;
	int		here_doc_res;
	t_fds	fds;

	if (argc < 5)
	{
		ft_printf("missing arguments");
		return (1);
	}
	here_doc_res = here_doc(&argc, argv);
	if (here_doc_res)
	{
			argc--;
			argv++;
			argv[1] = ft_strdup("temp.txt");
	}
	childs = input_parse(argc, argv, env);
	main_iter(env, here_doc_res, childs, &fds);
	waitpid(0, NULL, 0);
	free_childs(childs);
	if (here_doc_res)
		unlink("temp.txt");
	return (0);
}

void	main_iter(char **env, int here_doc_res, t_child **childs, t_fds *fds)
{
	int		i;
	int		id;
	t_vars	vars;

	i = 0;
	while (childs[i])
	{
		if (childs[i + 1])
			pipe(fds->after);
		id = fork();
		if (id < 0)
			exit (1);
		vars.here_doc_res = here_doc_res;
		vars.i = i;
		vars.id = id;
		vars.childs = childs;
		main_child(env, fds, vars);
		i++;
	}
}

void	main_child(char **env, t_fds *fds, t_vars vars)
{
	if (vars.id == 0)
	{
		if (vars.i == 0)
			child_first(vars.childs[vars.i], env, fds->after);
		else if (!vars.childs[vars.i + 1])
			child_last(vars.childs[vars.i], env,
				fds->before, vars.here_doc_res);
		else
			child_between(vars.childs[vars.i], env, fds->before, fds->after);
	}
	else
	{
		if (vars.i != 0)
			close_fd(fds->before);
		fds->before[0] = fds->after[0];
		fds->before[1] = fds->after[1];
	}
}
