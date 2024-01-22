/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:53:51 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/22 16:12:12 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
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
		dup2(fds[1], STDOUT_FILENO);
		close(data.file1);
		close(data.file2);
		close(fds[1]);
		close(fds[0]);
		if (execve(data.cmd[0].split[0], data.cmd[0].split, envp) < 0)
		{
			perror("Could not execve");
			exit(EXIT_FAILURE);
		}
	}
	close(fds[1]);
	pid_t	pid2;
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(data.file2, STDOUT_FILENO);
		close (fds[0]);
		close (data.file1);
		close(data.file2);
		if (execve(data.cmd[1].split[0], data.cmd[1].split, envp) < 0)
		{
			perror("Could not execve");
			exit(EXIT_FAILURE);
		}
	}
	close(fds[0]);
	close(data.file1);
	waitpid(pid, &status, 0);
	waitpid(pid2, &status, 0);

	clean(&data);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
} */