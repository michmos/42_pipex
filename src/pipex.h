/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 13:36:28 by mmoser        #+#    #+#                 */
/*   Updated: 2024/02/28 10:47:02 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../external_libs/src/ft_printf/ft_printf.h"
# include "../external_libs/src/get_next_line/get_next_line.h"
# include "../external_libs/src/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define ERROR -1

typedef struct s_pipe_info
{
	char	***cmds;
	int		pipe[2];
	int		here_doc;
	char	*hd_limiter;
	char	*infile;
	char	*outfile;
}			t_pipe_info;

// helper_foos.c
void		err_exit(char *str);
int			i_o_redirection(int input_fd, int output_fd);

// free_heap.c
void		free_ar3(void ***str);
void		free_ar2(void **pipes);
void		wait_free_exit(char ***cmds, int exit_status);

// cmd_pipeline.c
pid_t		cmd_pipeline(t_pipe_info *info, size_t num_childs, char **env);

// set_cmd_path.c
void		set_cmd_path(char ***cmds, char **env);

// main.c
char		***parsing(size_t size, char *argv[]);
int			main(int argc, char *argv[], char **env);

#endif
