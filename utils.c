/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:19:59 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/19 12:39:57 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->cmd_y)
	{
		j = 0;
		while (data->cmd[i].split[j])
		{
			free(data->cmd[i].split[j]);
			j++;
		}
		free (data->cmd[i].split);
		i++;
	}
	free(data->cmd);
}

void	qawk(t_data *data)
{
	int		i;
	int		j;
	char	*awk;

	i = 0;
	awk = "/usr/bin/awk";
	while (i < data->cmd_y)
	{
		j = 0;
		if (ft_strncmp(data->cmd[i].split[0], awk, 12) == 0)
		{
			while (data->cmd[i].split[j])
			{
				if (data->cmd[i].split[j][0] == 39)
				{
					data->cmd[i].split[j] = ft_strtrim(data->cmd[i].split[j], "'");
				}
				j++;
			}
		}
		i++;
	}
}
