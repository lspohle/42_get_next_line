/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 08:27:25 by lspohle           #+#    #+#             */
/*   Updated: 2023/01/12 15:20:50 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Allocates memory for buffer, and writes zeroed bytes to it
// Reads BUFFER_SIZE of data from fd into the buffer
// If read() returns 0, inf will be set to 0 (signals EOF)
// Returns buffer if successful
// Returns NULL if allocation/reading failed
char	*read_into_buffer(int fd, int *inf)
{
	char	*buffer;
	int		read_return;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_return = read(fd, buffer, BUFFER_SIZE);
	if (read_return == 0)
		*inf = 0;
	else if (read_return == -1)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

// Outlines the frame of the line
// If EOF, looks for the first occurrence of '\0'
// If INF, looks for the first occurrence of '\n'
// Remainder is set to remainings followed by line
// Returns the found line if successful
// Returns NULL if allocation failed
char	*found_line(char *occurrence, char **remainder, char *line, int *inf)
{
	char	*tmp;

	if (*inf == 0)
		occurrence = ft_strchr(*remainder, '\0');
	tmp = ft_substr(*remainder, 0, occurrence - *remainder + *inf);
	if (tmp == NULL)
		return (NULL);
	line = ft_strjoin(tmp, "");
	if (line == NULL)
		return (NULL);
	free(tmp);
	tmp = ft_strjoin(occurrence + *inf, "");
	if (tmp == NULL)
		return (NULL);
	free (*remainder);
	*remainder = tmp;
	return (line);
}

// Checks whether the remainder contains a valid line
// A valid line can either be caused by '\n' or by EOF
// If no line found, remainder is supplemented by buffer
// Remainder will be checked recursively again
// Returns the found line if successful
// Returns NULL if allocation failed
char	*check_for_line(int fd, char **remainder, char *line, int *inf)
{
	char	*occurrence;
	char	*tmp;
	char	*tmp2;

	occurrence = NULL;
	if (*remainder != NULL)
		occurrence = ft_strchr(*remainder, '\n');
	if (occurrence == NULL && *inf == 1)
	{
		tmp = read_into_buffer(fd, inf);
		if (tmp == NULL)
			return (NULL);
		tmp2 = ft_strjoin(*remainder, tmp);
		free(tmp);
		if (tmp2 == NULL)
			return (NULL);
		free (*remainder);
		*remainder = tmp2;
		line = check_for_line(fd, remainder, line, inf);
	}
	else
		line = found_line(occurrence, remainder, line, inf);
	return (line);
}

// Returns a valid line terminated by '\n' or '\0' read from fd
// Returns NULL if an error occurred or there is no line left
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	int			inf;

	if (fd <= -1)
		return (NULL);
	inf = 1;
	if (remainder == NULL)
		remainder = read_into_buffer(fd, &inf);
	line = check_for_line(fd, &remainder, NULL, &inf);
	if (line == NULL)
	{
		free(remainder);
		remainder = NULL;
	}
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// #define GREEN "\e[38;5;41m"
// #define ESCAPE "\033[0m"

// int main(void)
// {
// 	int		fd = open("test.txt", O_RDONLY);
// 	char	*line;

// 	printf(GREEN"File descriptor:"ESCAPE" %i\n", fd);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);

// 	close(fd);
// }
