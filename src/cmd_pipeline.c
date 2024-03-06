/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pipeline.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 12:21:38 by mmoser        #+#    #+#                 */
/*   Updated: 2024/03/01 09:52:29 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_in_out(size_t child_i, size_t num_childs, t_pipe_info *info, int last_read_end)
{
	int	fds[2];

	if (child_i == 0)
		fds[0] = open(info->infile, O_RDONLY);
	else
		fds[0] = last_read_end;
	if (child_i == num_childs - 1)
	{
		if (info->here_doc)
			fds[1] = open(info->outfile, O_WRONLY | O_APPEND | O_CREAT, 0664);
		else
			fds[1] = open(info->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	}
	else
	{
		if (close(info->pipe[0]) == ERROR)
			wait_free_exit(info->cmds, EXIT_FAILURE);
		fds[1] = info->pipe[1];
	}
	if (fds[0] == ERROR || fds[1] == ERROR || i_o_redirection(fds[0],
			fds[1]) == ERROR)
		wait_free_exit(info->cmds, EXIT_FAILURE);
}

static int	exec_here_doc(t_pipe_info *info)
{
	char	*buffer;
	size_t	strlen;

	strlen = ft_strlen(info->hd_limiter);
	while (1)
	{
		buffer = get_next_line(0);
		if (!buffer)
			wait_free_exit(info->cmds, EXIT_FAILURE);
		if (ft_strncmp(buffer, info->hd_limiter, strlen) == 0
			&& buffer[strlen] == '\n')
		{
			free(buffer);
			wait_free_exit(info->cmds, EXIT_SUCCESS);
		}
		write(info->pipe[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
}

static void	exec_cmd(int child_i, t_pipe_info *info, char **env)
{
	if (info->here_doc)
		execve(info->cmds[child_i - 1][0], info->cmds[child_i - 1], env);
	else
		execve(info->cmds[child_i][0], info->cmds[child_i], env);
	wait_free_exit(info->cmds, EXIT_FAILURE);
}

static void	close_unused_ends(int child_i, int num_childs, t_pipe_info *info, int read_end)
{
	if (child_i != num_childs - 1)
	{
		if (close(info->pipe[1]) == ERROR)
			wait_free_exit(info->cmds, EXIT_FAILURE);
	}
	if (child_i != 0)
	{
		if (close(read_end) == ERROR)
			wait_free_exit(info->cmds, EXIT_FAILURE);
	}
}

pid_t	cmd_pipeline(t_pipe_info *info, size_t num_childs, char **env)
{
	size_t	i;
	pid_t	pid;
	int		read_end;

	i = 0;
	read_end = -1;
	while (i < num_childs)
	{
		if (i < num_childs - 1 && pipe(info->pipe) == ERROR)
			wait_free_exit(info->cmds, EXIT_FAILURE);
		pid = fork();
		if (pid == ERROR)
			wait_free_exit(info->cmds, EXIT_FAILURE);
		else if (pid == 0)
		{
			if (i == 0 && info->here_doc)
				exec_here_doc(info);
			set_in_out(i, num_childs, info, read_end);
			exec_cmd(i, info, env);
		}
		close_unused_ends(i, num_childs, info, read_end);
		read_end = info->pipe[0];
		i++;
	}
	return (pid);
}
