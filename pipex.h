/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:54:17 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/17 12:20:36 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

# define PP ft_printf("prout")
# define DD(xxx) ft_printf("%d", xxx)
# define SS(xxx) ft_printf("%s", xxx)
# define CC(xxx) ft_printf("%c", xxx)

typedef struct s_cmd
{
	char	*cmd;
	char	**split;
}		t_cmd;

typedef struct s_data
{
	t_cmd	*cmd;
	int		cmd_y;
	int		file1;
	int		file2;
	char	**path;
	char	*temp;
}			t_data;

void	sep_arg(t_data *data);
int		path_helper(t_data *data, int k, char *full_path);
int		path(t_data *data);
void	parsing(t_data *data, int ac, char **av);
void	clean(t_data *data);

#endif /* PIPEX_H */