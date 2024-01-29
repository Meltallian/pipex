/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:35:24 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/29 13:46:42 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ini(t_data *data, int ac, char **av)
{
	if (ac != 5)
	{
		ft_putstr_fd("wrong synthax\n", 2);
		exit (1);
	}
	parsing(data, ac, av);
	sep_arg(data);
	if (path(data) < 0)
	{
		ft_putstr_fd("command not found\n", 2);
	}
	qawk(data);
	return (0);
}

void	child_1(t_data *data, int *fds, char **envp)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		exit(0);
	}
	if (data->pid == 0)
	{
		dup2(data->file1, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(data->file1);
		close(data->file2);
		close(fds[1]);
		close(fds[0]);
		if (data->file1 == -1)
			exit(0);
		if (execve(data->cmd[0].split[0], data->cmd[0].split, envp) < 0)
		{
			exit(0);
		}
	}
}

void	child_2(t_data *data, int *fds, char **envp)
{
	data->pid2 = fork();
	if (data->pid2 == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		exit(0);
	}
	if (data->pid2 == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(data->file2, STDOUT_FILENO);
		close (fds[0]);
		close (data->file1);
		close(data->file2);
		if (data->file2 == -1)
			exit(0);
		if (execve(data->cmd[1].split[0], data->cmd[1].split, envp) < 0)
		{
			exit(0);
		}
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;
	int		fds[2];

	ini(&data, ac, av);
	if (pipe(fds) == -1)
	{
		ft_putstr_fd("pipe error\n", 2);
		exit(0);
	}
	child_1(&data, fds, envp);
	close(fds[1]);
	child_2(&data, fds, envp);
	close(fds[0]);
	close(data.file1);
	close(data.file2);
	clean(&data);
	return (wait_last(data.pid2));
}
