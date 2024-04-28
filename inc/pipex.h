/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:04:36 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 18:52:34 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include "libft.h"
# include "ft_printf.h"

typedef struct s_pipe
{
	int		a[2];
	int		b[2];
} t_pipe;

typedef struct s_param
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
} t_param;

//pipex_utils.c
void	init_param(t_pipe *fds, t_param *param);
void	terminate(char *msg);

//exec_proc.c
void	execute_proc(t_param param, t_list *path, t_pipe fds);
void	wait_proc(int argc);

#endif
