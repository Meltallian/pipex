/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:17:18 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/30 14:07:25 by jbidaux          ###   ########.fr       */
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
