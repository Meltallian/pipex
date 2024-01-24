/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:45:02 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/24 15:08:49 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fd_closing(t_data *data, int **fds)
{
	int	j;

	j = 0;
	while (j < data->cmd_y - 1)
	{
		close (fds[j][0]);
		close (fds[j][1]);
		j++;
	}
}

void	child(t_data *data, int **fds, char **envp, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		exit(0);
	}
	if (pid == 0)
	{
		dup2(fds[i - 1][0], STDIN_FILENO);
		dup2(fds[i][1], STDOUT_FILENO);
		close(data->file1);
		close(data->file2);
		fd_closing(data, fds);
		if (execve(data->cmd[i].split[0], data->cmd[i].split, envp) < 0)
			exit(0);
	}
}

void	child_start(t_data *data, int **fds, char **envp)
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
		dup2(fds[0][1], STDOUT_FILENO);
		close(data->file1);
		close(data->file2);
		fd_closing(data, fds);
		if (data->file1 == -1)
			exit(0);
		if (execve(data->cmd[0].split[0], data->cmd[0].split, envp) < 0)
			exit(0);
	}
}

void	child_end(t_data *data, int **fds, char **envp, int i)
{
	data->pid2 = fork();
	if (data->pid2 == -1)
	{
		ft_putstr_fd("fork error\n", 2);
		exit(0);
	}
	if (data->pid2 == 0)
	{
		dup2(fds[i - 1][0], STDIN_FILENO);
		dup2(data->file2, STDOUT_FILENO);
		close(data->file1);
		close(data->file2);
		fd_closing(data, fds);
		if (data->file2 == -1)
			exit(0);
		if (execve(data->cmd[i].split[0], data->cmd[i].split, envp) < 0)
			exit(0);
	}
}
