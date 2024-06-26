/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:47:59 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 22:06:06 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"

# define READ 0
# define WRITE 1

typedef struct s_param
{
	int		argc;
	char	**argv;
	char	**envp;
	int		here_doc;
	char	*doc_name;
}	t_param;

//here_doc_bonus.c
char	*here_doc(char *limiter);

//exec_proc_bonus.c
void	execute_procs(t_param arg, int argc);

//pipex_utils_bonus.c
void	terminate(char *msg);
void	parent_error(t_param arg, int n);
int		wait_proc(t_param arg);
char	*extract_first_command(char *cmd);

//pipex_utils_2_bonus.c
void	control_fildes(int fd_a[2], int fd_b[2], t_param arg, int n);
char	*find_path(char *cmd, char **pathv);
void	close_remainder_fds(int fd_a[2], int fd_b[2], int n);
char	**parse_envp_path(char *envp[]);

#endif
