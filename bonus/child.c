/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:45:02 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/23 12:14:04 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(t_data *data, int *fds, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(0);
	}
	if (pid == 0)
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
			exit(0);
		}
	}
}

void	child_start(t_data *data, int *fds, char **envp)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork error");
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
			perror("Could not execve");
			exit(0);
		}
	}
}

void	child_end(t_data *data, int *fds, char **envp)
{
	data->pid2 = fork();
	if (data->pid2 == -1)
	{
		perror("fork error");
		exit(0);
	}
	if (data->pid2 == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(data->file2, STDOUT_FILENO);
		close(fds[0]);
		close(data->file1);
		close(data->file2);
		if (data->file2 == -1)
			exit(0);
		if (execve(data->cmd[1].split[0], data->cmd[1].split, envp) < 0)
		{
			perror("Could not execve");
			exit(0);
		}
	}
}
