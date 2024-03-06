/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helper_foos1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 17:26:27 by mmoser        #+#    #+#                 */
/*   Updated: 2024/02/28 10:46:54 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	i_o_redirection(int input_fd, int output_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (ERROR);
	if (input_fd != STDIN_FILENO)
	{
		if (close(input_fd) == -1)
			return (ERROR);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (ERROR);
	if (output_fd != STDOUT_FILENO)
	{
		if (close(output_fd) == -1)
			return (ERROR);
	}
	return (0);
}
