/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:17:18 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/24 11:06:22 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	path_helper(t_data *data, int k, char *full_path)
{
	int	j;
	int	i;

	i = 0;
	while (data->path[i])
	{
		j = 0;
		while (j < data->cmd_y)
		{
			data->temp = ft_strjoin(data->path[i], "/");
			full_path = ft_strjoin(data->temp, data->cmd[j].split[0]);
			free(data->temp);
			if (access(full_path, X_OK) == 0)
			{
				free(data->cmd[j].split[0]);
				data->cmd[j].split[0] = full_path;
				k++;
			}
			else
				free(full_path);
			j++;
		}
		i++;
	}
	return (k);
}

int	path(t_data *data)
{
	const char	*path = getenv("PATH");
	char		*full_path;
	int			k;
	int			i;

	k = 0;
	full_path = "";
	data->path = ft_split(path, ':');
	k = path_helper(data, k, full_path);
	i = 0;
	while (data->path[i])
	{
		free(data->path[i]);
		i++;
	}
	free(data->path);
	if (k != data->cmd_y)
		return (-1);
	return (0);
}

void	helper_fd_files(int ac, char **av, int i)
{
	if (access(av[ac - 1], F_OK) != 0 && i == 1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	else if (access(av[ac - 1], W_OK != 0) && i == 1)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	else if (open(av[ac - 1], O_DIRECTORY) > -1 && i == 1)
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

	i = 0;
	if (access(av[1], F_OK) != 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		i = 1;
	}
	else if (access(av[1], R_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		i = 1;
	}
	helper_fd_files(ac, av, i);
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
	fd_files(ac, av);
	data->file1 = open(av[1], O_RDONLY);
	data->file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
