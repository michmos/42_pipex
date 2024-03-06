/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoser <mmoser@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:39:40 by mmoser            #+#    #+#             */
/*   Updated: 2024/02/08 15:32:32 by mmoser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

static char	*get_env_path(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			return (env[i]);
		i++;
	}
	write(STDERR_FILENO, "ERROR: PATH not found\n", 22);
	return (NULL);
}

static char	**get_bin_paths(char **env)
{
	char	**bin_paths;
	char	*env_path;
	char	*temp;
	size_t	i;

	env_path = get_env_path(env);
	if (!env_path)
		return (NULL);
	bin_paths = ft_split(env_path + 5, ':');
	if (!bin_paths)
		return (NULL);
	i = 0;
	while (bin_paths[i])
	{
		temp = ft_strjoin(bin_paths[i], "/");
		if (!temp)
		{
			free_ar2((void **) bin_paths);
			return (NULL);
		}
		free(bin_paths[i]);
		bin_paths[i] = temp;
		i++;
	}
	return (bin_paths);
}

static int	join_path_and_command(char **cmd, char **bin_paths)
{
	char	*temp;
	size_t	j;

	j = 0;
	while (bin_paths[j])
	{
		temp = ft_strjoin(bin_paths[j], *cmd);
		if (!temp)
		{
			perror("ERROR occurred when creating command path");
			return (ERROR);
		}
		if (access(temp, X_OK) == 0)
		{
			free(*cmd);
			*cmd = temp;
			return (0);
		}
		free(temp);
		j++;
	}
	return (0);
}

void	set_cmd_path(char ***cmds, char **env)
{
	size_t	i;
	char	**bin_paths;

	bin_paths = get_bin_paths(env);
	if (!bin_paths)
	{
		free_ar3((void ***) cmds);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (cmds[i])
	{
		if (access(cmds[i][0], X_OK) != 0)
		{
			if (join_path_and_command(cmds[i], bin_paths) == ERROR)
			{
				free_ar3((void ***) cmds);
				free_ar2((void **) bin_paths);
				exit (EXIT_FAILURE);
			}
		}
		i++;
	}
	free_ar2((void **) bin_paths);
}
