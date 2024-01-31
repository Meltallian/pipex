/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:53:51 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/31 10:02:43 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ini(t_data *data, int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd("wrong syntax\n", 2);
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

void	main_helper(t_data *data, int **fds, int ac, char *envp[])
{
	int	i;

	child_start(data, fds, envp);
	i = 1;
	while (i < ac - 4 && ac > 5)
	{
		child(data, fds, envp, i);
		i++;
	}
	child_end(data, fds, envp, i);
	i = 0;
	while (i < data->cmd_y - 1)
	{
		close (fds[i][0]);
		close (fds[i][1]);
		i++;
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_data	data;
	int		**fds;
	int		i;

	ini(&data, ac, av);
	fds = malloc((ac - 4) * sizeof(int *));
	i = 0;
	while (i < ac - 4)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (pipe(fds[i]) == -1)
		{
			ft_putstr_fd("pipe error\n", 2);
			exit(0);
		}
		i++;
	}
	main_helper(&data, fds, ac, envp);
	close(data.file1);
	close(data.file2);
	clean(&data, fds, ac);
	return (wait_last(data.pid2));
}
