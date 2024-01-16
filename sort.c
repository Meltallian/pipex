/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbidaux <jeremie.bidaux@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:22:56 by jbidaux           #+#    #+#             */
/*   Updated: 2024/01/16 15:11:12 by jbidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main()
{
	int		fds[2];
	pid_t	pid;

	pipe(fds);
	pid = fork(); //process ID de l'enfant qui doit etre 0.
	if (pid == 0)
	{
		dup2(fds[0], STDIN_FILENO); //fds[0] donates its data to the file descriptor 0 std0. fds[0] is the read end of the pipe
		close(fds[0]); //close the to read end of the pipe. Unused by the child. since stdin is now the read end of the pipe
		close(fds[1]); //close the to write end of the pipe. Unused by the child.
		char *argv[] = {(char *)"sort", NULL}; //create argument vector for the sort command
		if (execvp(argv[0], argv) < 0)
			exit (0); //execute the sort command and exit if it fails;
	}

	// if we reach here, we are in the parent process
	close(fds[0]); //close the read end of the pipe. Unused by the parent.
	const char *words[] = {"pear", "peach", "apple", "banana", "orange"};
	// write input to the writable file descriptor so it can be read by the child.
	size_t numwords = sizeof(words) / sizeof(words[0]);
	for (size_t i = 0; i < numwords; i++)
		dprintf(fds[1], "%s\n", words[i]);
	// send EOF so child can continue (child blocks until all input has been processed)
	close(fds[1]);

	int status;
	pid_t wpid = waitpid(pid, &status, 0); //wait for the child to finish
	return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}
