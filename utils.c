/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:19:59 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/17 12:20:24 by jbidaux          ###   ########.fr       */
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
