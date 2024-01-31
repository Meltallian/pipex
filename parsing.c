/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:17:18 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/31 10:12:46 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	helper_fd_files(int ac, char **av, int i, int j)
{
	if (access(av[ac - 1], W_OK) != 0 && access(av[ac - 1], F_OK) == 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	if (access(av[ac - 1], F_OK) != 0 && i == 1 && j == 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	else if (open(av[ac - 1], O_DIRECTORY) != 0 && i == 1)
	{
		ft_putstr_fd("is a directory: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
}

void	fd_files(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (access(av[1], F_OK) != 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		i = 1;
		j++;
	}
	else if (access(av[1], R_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		i = 1;
	}
	helper_fd_files(ac, av, i, j);
}

void	parsing_helper(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_y)
	{
		if (empty_or_space(data->cmd[i].cmd) == 1)
		{
			ft_putstr_fd("command not found\n", 2);
			exit (1);
		}
		if (empty_or_space(data->cmd[i].cmd) == 2)
			ft_putstr_fd("command not found\n", 2);
		i++;
	}
}

void	parsing(t_data *data, int ac, char **av)
{
	int	i;

	i = 2;
	data->cmd = malloc((ac - 3) * sizeof(t_cmd));
	if (data->cmd == NULL)
		exit (1);
	while (av[i + 1])
	{
		data->cmd[i - 2].cmd = av[i];
		i++;
	}
	data->cmd_y = ac - 3;
	parsing_helper(data);
	fd_files(ac, av);
	data->file1 = open(av[1], O_RDONLY);
	data->file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
