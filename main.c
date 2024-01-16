/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:35:24 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/16 16:49:38 by jbidaux          ###   ########.fr       */
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

void	sep_arg(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_y)
	{
		data->cmd[i].split = ft_split(data->cmd[i].cmd, ' ');
		i++;
	}
}

int	path(t_data *data)
{
	const char	*path = getenv("PATH");
	char	**split;
	char	*full_path;
	char	*temp;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	split = ft_split(path, ':');
	while (split[i])
	{
		j = 0;
		while (j < data->cmd_y)
		{
			temp = ft_strjoin(split[i], "/");
			full_path = ft_strjoin(temp, data->cmd[j].split[0]);
			free(temp);
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
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	if (k != data->cmd_y)
		return (-1);
	return (0);
}
//       /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin
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
	if (data->file1 < 0)
		perror("Error opening file1");
	data->file2 = open(av[data->cmd_y + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->file2 < 0)
		perror("Error opening file2");
}

int	ini(t_data *data, int ac, char **av)
{
	parsing(data, ac, av);
	sep_arg(data);
	if (path(data) < 0)
	{
		perror("wrong commands");
		exit(0);
	}
	return (0);
}

int	main(int ac, char *av[]/* , char *envp[] */)
{
	t_data	data;
//	int		fds[2];
//	pid_t	pid;
	int	i;

	ini(&data, ac, av);
/* 	pipe(fds);
	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(data.file1, STDIN_FILENO);
		close(data.file1);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
		close(data.file2);
		if (execve("PATH", data.cmd[0].split, av[1]) < 0)
			perror("Could not execve");
	} */

//	close(fds[0])
	i = 0;
	while(i < ac - 3)
	{
		ft_printf("%s\n", data.cmd[i].cmd);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		SS(data.cmd[0].split[i]);
		SS("\n");
		i++;
	}
	// SS(getenv("PATH"));
	clean(&data);
	return (0);
}

// PATH= /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin
//       /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin