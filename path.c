/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:17:18 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/22 12:19:07 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sep_arg(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_y)
	{
		if (ft_strncmp(data->cmd[i].cmd, "awk", 3) == 0)
		{
			data->cmd[i].split = ft_split_2(data->cmd[i].cmd, ' ');
		}
		else
		{
			data->cmd[i].split = ft_split(data->cmd[i].cmd, ' ');
		}
		i++;
	}
}

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
	data->file1 = open(av[1], O_RDONLY);
	if (access(av[1], F_OK) != 0)
		ft_printf("no such file or directory: %s\n", av[1]);
	else if (access(av[1], R_OK) != 0)
		ft_printf("permission denied: %s\n", av[1]);
	data->file2 = open(av[data->cmd_y + 2], O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (access(av[data->cmd_y + 2], W_OK != 0))
	{
		ft_printf("permission denied: %s\n", av[data->cmd_y + 2]);
		exit (EXIT_FAILURE);
	}
	else if (open(av[data->cmd_y + 2], O_DIRECTORY > -1))
	{
		ft_printf("is a directory: %s\n", av[data->cmd_y + 2]);
		exit (EXIT_FAILURE);
	}
}
