/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:35:24 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/19 16:55:09 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ini(t_data *data, int ac, char **av)
{
	parsing(data, ac, av);
	sep_arg(data);
	if (path(data) < 0)
	{
		perror("command not found");
		exit(0);
	}
/* 	int	i = 0;
	while (data->cmd[1].split[i])
	{
		printf("%s", data->cmd[1].split[i]);
		printf("\n");
		i++;
	} */
	qawk(data);
	return (0);
}

void	child_1(t_data *data, int *fds, char **envp)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (data->pid == 0)
	{
		dup2(data->file1, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(data->file1);
		close(data->file2);
		close(fds[1]);
		close(fds[0]);
		if (execve(data->cmd[0].split[0], data->cmd[0].split, envp) < 0)
		{
			perror("Could not execve");
			exit(EXIT_FAILURE);
		}
	}
}

void	child_2(t_data *data, int *fds, char **envp)
{
	data->pid2 = fork();
	if (data->pid2 == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (data->pid2 == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(data->file2, STDOUT_FILENO);
		close (fds[0]);
		close (data->file1);
		close(data->file2);
		if (execve(data->cmd[1].split[0], data->cmd[1].split, envp) < 0)
		{
			perror("Could not execve");
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;
	int		fds[2];
	int		status;

	ini(&data, ac, av);
	if (pipe(fds) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	child_1(&data, fds, envp);
	close(fds[1]);
	child_2(&data, fds, envp);
	close(fds[0]);
	close(data.file1);
	close(data.file2);
	waitpid(data.pid, &status, 0);
	waitpid(data.pid2, &status, 0);
	clean(&data);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

// PATH= /usr/local/bin:/usr/bin:/bin:/usr/sbin:
// /sbin:/usr/local/munki:/Library/Apple/usr/bin

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