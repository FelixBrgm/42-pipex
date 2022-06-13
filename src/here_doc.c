/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:53:19 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/12 23:18:45 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	here_doc(int *argc, char **argv)
{
	int		fd;
	char	*temp;
	char	*end;

	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
	{
		close(open(argv[*argc -1], O_CREAT | O_WRONLY
				| O_TRUNC, S_IRUSR | S_IWUSR));
		return (0);
	}
	close(open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR));
	end = ft_strjoin(argv[2], "\n");
	fd = open("temp.txt", O_WRONLY);
	temp = get_next_line(STDIN_FILENO);
	while (temp && ft_strncmp(temp, end, ft_strlen(temp) + ft_strlen(end)) != 0)
	{
		ft_putstr_fd(temp, fd);
		temp = get_next_line(STDIN_FILENO);
	}
	close(fd);
	return (1);
}
