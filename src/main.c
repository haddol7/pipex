/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:12:06 by daeha             #+#    #+#             */
/*   Updated: 2024/04/29 15:54:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cmd1 == argv[2]
// cmdn == argv[argc - 2]
// 0 1 2 3 4
// $> ./pipex file1 cmd1 cmd2 file2
// $> ./pipex input.txt "ls -a" "cat" output.txt

int	wait_proc(t_pipe fds, int argc)
{
	int i;
	int	status;

	i = 3;
	close(3);
	close(4);

	while (i < argc)
	{
		wait(&status);
		i++;
	}
	if (WIFSIGNALED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_pipe fds;
	t_param	param;
	
	param.argc = argc;
	param.argv = argv;
	param.envp = envp;
	param.path = NULL;
	if (argc < 5)
		terminate("test");
	// if (!ft_strncmp(argv[1], "here_doc", 9))
	// 	here_doc();
	init_param(&fds, &param);
	execute_procs(&fds, param);
	return (wait_proc(fds, argc));
}
