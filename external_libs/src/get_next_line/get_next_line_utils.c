/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 11:29:58 by mmoser        #+#    #+#                 */
/*   Updated: 2023/11/07 13:28:18 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_and_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*replace_str(char *src, size_t size_to_allocate, bool free_source)
{
	size_t	i;
	size_t	src_len;
	char	*cpy_s;

	cpy_s = ft_calloc(size_to_allocate, sizeof(char));
	if (cpy_s == NULL)
	{
		if (free_source == 1)
			ft_free_and_null(&src);
		return (NULL);
	}
	i = 0;
	src_len = ft_strlen(src);
	while (i < src_len && i < size_to_allocate - 1)
	{
		cpy_s[i] = src[i];
		i++;
	}
	if (free_source == 1)
		ft_free_and_null(&src);
	return (cpy_s);
}
