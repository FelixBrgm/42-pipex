/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:15:19 by fbruggem          #+#    #+#             */
/*   Updated: 2022/06/09 09:32:05 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libs/libs.h"
# include <unistd.h>

typedef struct s_input
{
	char	*cmd1;
	char	*cmd2;
	char	*cmd1_dst;
	char	*cmd2_dst;
	char	*file1;
	char	*file2;
}				t_input;

#endif
