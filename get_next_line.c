/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:38:48 by lspohle           #+#    #+#             */
/*   Updated: 2023/01/11 14:15:23 by lspohle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*read_buffer_size(int fd, int *inf)
{
	char	*buffer;
	int		return_of_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	return_of_read = read(fd, buffer, BUFFER_SIZE);
	if (return_of_read == -1)
	{
		free(buffer);
		return (NULL);
	}
	else if (return_of_read == 0)
		*inf = 0;
	return (buffer);
}

char	*line_found(char **remainder, char	*occurrence, char *line, int *inf)
{
	char	*tmp;

	if (*remainder && *inf == 0)
		occurrence = ft_strchr(*remainder, '\0');
	line = ft_substr(*remainder, 0, occurrence - *remainder + *inf);
	if (line == NULL)
		return (NULL);
	tmp = ft_strjoin(occurrence + *inf, "");
	if (tmp == NULL)
		return (NULL);
	free (*remainder);
	*remainder = tmp;
	return (line);
}

char	*check_for_line(int fd, char **remainder, char *line, int *inf)
{
	char	*occurrence;
	char	*tmp;
	char	*tmp2;

	occurrence = NULL;
	if (*remainder != NULL)
		occurrence = ft_strchr(*remainder, '\n');
	if (occurrence == 0 && *inf == 1)
	{
		tmp = read_buffer_size(fd, inf);
		if (tmp == NULL)
			return (NULL);
		tmp2 = ft_strjoin(*remainder, tmp);
		if (tmp2 == NULL)
			return (NULL);
		free (tmp);
		free (*remainder);
		*remainder = tmp2;
		line = check_for_line(fd, remainder, line, inf);
	}
	else
		line = line_found(remainder, occurrence, line, inf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	int			inf;

	if (fd < 0)
		return (NULL);
	inf = 1;
	if (remainder == NULL)
		remainder = read_buffer_size(fd, &inf);
	line = check_for_line(fd, &remainder, NULL, &inf);
	if (line == NULL)
	{
		free (remainder);
		remainder = NULL;
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*tmp;

// 	fd = open("test.txt", O_RDONLY);

// 	tmp = get_next_line(fd);
// 	printf("%s", tmp);
// 	free(tmp);
// 	tmp = get_next_line(fd);
// 	printf("%s", tmp);
// 	free(tmp);
// 	tmp = get_next_line(fd);
// 	printf("%s", tmp);
// 	free(tmp);
// 	tmp = get_next_line(fd);
// 	printf("%s", tmp);
// 	free(tmp);
// 	tmp = get_next_line(fd);
// 	printf("%s", tmp);
// 	free(tmp);
// 	tmp = get_next_line(fd);
// 	printf("%s", tmp);
// 	free(tmp);

// 	close(fd);
// }
