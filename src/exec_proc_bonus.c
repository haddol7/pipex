/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:33:52 by daeha             #+#    #+#             */
/*   Updated: 2024/04/30 18:28:08 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	command_proc(int read[2], int write[2], t_param arg, int n);
static void	redirect_io(int read[2], int write[2], t_param arg, int n);
static void	redirect_file_io(int read[2], int write[2], t_param arg, int n);
static char	*find_path(char *cmd, char **pathv);
static char	**parse_envp_path(char *envp[]);

void	execute_procs(t_param arg, int argc)
{
	int		fd_a[2];
	int		fd_b[2];
	int		pid;
	int		n;

	n = 1;

	fd_a[0] = -1;
	fd_a[1] = -2;
	fd_b[0] = -3;
	fd_b[1] = -4;
	if (arg.here_doc == 1)
		argc--;
	while (++n < argc - 1)
	{
		control_fildes(fd_a, fd_b, arg, n);
		//dprintf(2, "%d-th process : %d %d | %d %d\n", n, fd_a[0], fd_a[1], fd_b[0], fd_b[1]);
		pid = fork();
		if (pid == -1)
			terminate("pipex: fork");
		else if (pid == 0)
		{
			if (n % 2 == 0)
				command_proc(fd_b, fd_a, arg, n);
			else
				command_proc(fd_a, fd_b, arg, n);
		}
	}
	//printf("%d, ", fd_a[0]);
	close(fd_a[0]);
	//printf("%d, ", fd_a[1]);
	close(fd_a[1]);
	//printf("%d, ", fd_b[0]);
	close(fd_b[0]);
	//printf("%d\n", fd_b[1]);
	close(fd_b[1]);
}

static void	command_proc(int read[2], int write[2], t_param arg, int n)
{
	char	*cmd_path;
	char	**cmd_argv;
	char	**path;

	//dprintf(2, "%d process : %d %d | %d %d\n", n, read[0], read[1], write[0], write[1]);

	redirect_io(read, write, arg, n);
	path = parse_envp_path(arg.envp);
	if (arg.here_doc == 1)
		n++;
	cmd_path = find_path(arg.argv[n], path);
	cmd_argv = ft_split(arg.argv[n], ' ');
	if (execve(cmd_path, cmd_argv, arg.envp) == -1)
		terminate("pipex: execve");
}

static void	redirect_io(int read[2], int write[2], t_param arg, int n)
{	
	if (n == 2 || n + arg.here_doc == arg.argc - 2)
		return (redirect_file_io(read, write, arg, n));
	close(read[WRITE]);
	dup2(read[READ], STDIN_FILENO);
	close(read[READ]);
	close(write[READ]);
	dup2(write[WRITE], STDOUT_FILENO);
	close(write[WRITE]);
}


static void	redirect_file_io(int read[2], int write[2], t_param arg, int n)
{
	int fd;

	fd = -1;
	if (n == 2)
	{
		close(write[READ]);
		if (arg.here_doc)
			fd = open(arg.doc_name, O_RDONLY, 0666);
		else
			fd = open(arg.argv[1], O_RDONLY, 0666);
		if (fd == -1)
			terminate("pipex: input");
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(write[WRITE], STDOUT_FILENO);
		close(write[WRITE]);
	}
	else
	{
		close(read[WRITE]);
		fd = open(arg.argv[arg.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			terminate("pipex: output");
		dup2(read[READ], STDIN_FILENO);
		close(read[READ]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}


static char	*find_path(char *cmd, char **pathv)
{
	char	*path;
	char	*cmd_trim;
	int		i;

	i = -1;
	cmd_trim = extract_first_command(cmd);
	while (pathv[++i] != NULL)
	{
		if (!access(cmd_trim, F_OK | X_OK))
			return (cmd_trim);
	}
	while (pathv != NULL)
	{	
		path = ft_strjoin(*pathv, cmd_trim);
		if (!access(path, F_OK | X_OK))
			return (path);
		free(path);
		pathv++;
	}
	return (NULL);
}

static char	**parse_envp_path(char *envp[])
{
	int		i;
	char	*str_path;

	i = 0;
	while (envp[i])
	{	
		if (!ft_strncmp(envp[i], "PATH=", 5))
			str_path = envp[i] + 5;
		i++;
	}
	return (ft_split(str_path, ':'));
}
