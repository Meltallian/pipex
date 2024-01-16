/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:54:17 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/16 13:30:38 by jbidaux          ###   ########.fr       */
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
}			t_data;


#endif /* PIPEX_H */