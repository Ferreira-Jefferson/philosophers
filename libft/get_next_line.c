/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:24:36 by jtertuli          #+#    #+#             */
/*   Updated: 2025/08/07 09:43:43 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_if_error(char **stash, char *temp_line)
{
	ft_to_free((void **) stash);
	ft_to_free((void **) &temp_line);
	return (-1);
}

static int	search_newline(char **stash, char **line)
{
	int		count;
	char	*temp_rest;
	char	*temp_line;

	count = 0;
	while (*stash && (*stash)[count])
	{
		if ((*stash)[count] == '\n')
		{
			temp_line = ft_substr(*stash, 0, count + 1);
			if (!temp_line)
				return (free_if_error(stash, NULL));
			temp_rest = ft_strdup(*stash + count + 1);
			if (!temp_rest)
				return (free_if_error(stash, temp_line));
			free(*stash);
			*stash = temp_rest;
			*line = temp_line;
			return (1);
		}
		count++;
	}
	return (0);
}

static char	*read_content(int fd, char **stash, int *read_error)
{
	char	*buffer;
	ssize_t	bytes;
	char	*old_stash;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
	{
		*read_error = bytes;
		return (ft_to_free((void **) &buffer));
	}
	buffer[bytes] = '\0';
	old_stash = *stash;
	*stash = ft_strjoin(*stash, buffer);
	if (!*stash)
		return (ft_to_free((void **) &buffer));
	free(old_stash);
	free(buffer);
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;
	int			read_error;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	while (1)
	{
		read_error = 0;
		if (search_newline(&stash[fd], &line) == 1)
			return (line);
		if (!read_content(fd, &stash[fd], &read_error) || read_error)
			break ;
	}
	if (stash[fd] && stash[fd][0] && !read_error)
	{
		line = stash[fd];
		stash[fd] = NULL;
		return (line);
	}
	return (ft_to_free((void **) &stash[fd]));
}
