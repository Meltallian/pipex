/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:35:24 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/17 14:43:09 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//       /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin

int	ini(t_data *data, int ac, char **av)
{
	parsing(data, ac, av);
	sep_arg(data);
	if (path(data) < 0)
	{
		perror("wrong commands");
		exit(0);
	}
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;
	int		fds[2];
	pid_t	pid;
	int		status;
	pid_t	wpid;

	ini(&data, ac, av);
	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(data.file1, STDIN_FILENO);
		close(data.file1);
		dup2(data.file2, STDOUT_FILENO);
		close(data.file2);
		close(fds[1]);
		close(fds[0]);
		close(data.file2);
		if (execve(data.cmd[0].split[0], data.cmd[0].split, envp) < 0)
		{
			perror("Could not execve");
			exit(EXIT_FAILURE);
		}
	}
	close(fds[1]);
	close(fds[0]);
	close(data.file1);
	close(data.file2);
	wpid = waitpid(pid, &status, 0); //wait for the child to finish
	clean(&data);
	if (wpid == pid && WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

// PATH= /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin

/* 	i = 0;
	while(i < ac - 3)
	{
		ft_printf("%s\n", data.cmd[i].cmd);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		SS(data.cmd[0].split[i]);
		SS("\n");
		i++;
	}
	i = 0;
	while (i < 4)
	{
		SS(data.cmd[1].split[i]);
		SS("\n");
		i++;
	}
	i = 0;
	while (i < 4)
	{
		SS(data.cmd[2].split[i]);
		SS("\n");
		i++;
	} */
	// SS(getenv("PATH"));