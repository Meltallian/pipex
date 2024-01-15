/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:35:24 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/15 18:21:03 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[]/* , char *envp[] */)
{
	t_data	data;
	int	i;

	i = 2;
	data.cmd = malloc((ac - 3) * sizeof(char*));
	if (data.cmd == NULL)
		return (-1);
	while (av[i + 1])
	{
		data.cmd[i - 2] = av[i];
		i++;
	}
	i = 0;
	while(i < ac - 3)
	{
		printf("%s\n", data.cmd[i]);
		i++;
	}
	free(data.cmd);
	return (0);
}

//PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin;