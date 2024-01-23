/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:54:17 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/23 15:16:35 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>

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
	pid_t	pid;
	pid_t	pid2;
}			t_data;

void	sep_arg(t_data *data);
int		path_helper(t_data *data, int k, char *full_path);
int		path(t_data *data);
void	helper_fd_files(int ac, char **av, int i);
void	fd_files(int ac, char **av);
void	parsing(t_data *data, int ac, char **av);
void	clean(t_data *data);
void	child_start(t_data *data, int (*fds)[2], char **envp);
void	child(t_data *data, int (*fds)[2], char **envp, int i);
void	child_end(t_data *data, int (*fds)[2], char **envp, int i);
void	qawk(t_data *data);
char	**ft_split_2(const char *s, const char c);
int		wait_last(int last_pid);

#endif /* PIPEX_BONUS_H */