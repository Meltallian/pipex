/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:53:51 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/23 12:14:07 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ini(t_data *data, int ac, char **av)
{
	if (ac != 5)
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
	if (pipe(fds[0]) == -1)
	{
		perror("pipe error");
		exit(0);
	}
	child_start(&data, fds[i], envp);
	close(fds[i][1]);
	child(&data, fds[i], envp);
	child_end(&data, fds[i], envp);
	close(fds[0][0]);
	close(data.file1);
	close(data.file2);
	clean(&data);
	return (wait_last(data.pid2));
}
