/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_heap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 12:12:42 by mmoser        #+#    #+#                 */
/*   Updated: 2024/02/28 10:46:25 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_ar3(void ***str)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return ;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != NULL)
		{
			free(str[i][j]);
			j++;
		}
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_ar2(void **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	wait_free_exit(char ***cmds, int exit_status)
{
	int	temp;

	temp = errno;
	while (wait(NULL) != -1)
		;
	errno = temp;
	if (cmds)
	{
		free_ar3((void ***)cmds);
	}
	exit(exit_status);
}
