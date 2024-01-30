/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:19:59 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/30 11:38:07 by jbidaux          ###   ########.fr       */
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

/**
 * @brief returns 1 if string is empty and 2 if cell 0 of string is a space.
 *
 * @param str
 * @return int
 */
int	empty_or_space(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (1);
	if (str[0] == ' ')
		return (2);
	return (0);
}

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
					data->cmd[i].split[j]
						= ft_strtrim(data->cmd[i].split[j], "'");
				}
				j++;
			}
		}
		i++;
	}
}

int	wait_last(int last_pid)
{
	int	status;
	int	pid;

	while (1)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == -1)
			break ;
		else if (pid == last_pid)
			return (WEXITSTATUS(status));
	}
	return (42);
}
