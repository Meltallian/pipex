/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:53:51 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/23 16:45:46 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ini(t_data *data, int ac, char **av)
{
	if (ac < 4)
	{
		perror("wrong synthax\n");
		exit(1);
	}
	parsing(data, ac, av);
	sep_arg(data);
	if (path(data) < 0)
	{
		perror("command not found\n");
		exit(0);
	}
	qawk(data);
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;
	int		fds[ac - 4][2];
	int		i;

	i = 0;
	ini(&data, ac, av);
	while (i < ac - 4)
	{
		if (pipe(fds[i]) == -1)
		{
			perror("pipe error");
			exit(0);
		}
		i++;
	}
	child_start(&data, fds, envp);
	i = 1;
	while (i < ac - 4 && ac > 5)
	{
		child(&data, fds, envp, i);
		i++;
	}
	child_end(&data, fds, envp, i);
	i = 0;
	while (i < data.cmd_y - 1)
	{
		close (fds[i][0]);
		close (fds[i][1]);
		i++;
	}
	close(data.file1);
	close(data.file2);
	clean(&data);
	return (wait_last(data.pid2));
}
