/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lineV4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:24:46 by fszendzi          #+#    #+#             */
/*   Updated: 2023/05/28 16:24:53 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

int	open_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	return (fd);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
		return (0);
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (ch == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	unsigned char		*dest;
	const unsigned char	*src;
	size_t				i;

	if (!destination && !source)
		return (NULL);
	dest = destination;
	src = source;
	i = 0;
	while (i < num)
	{
		dest[i] = src[i];
		i++;
	}
	return (destination);
}


char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	static ssize_t	bytes_in_buffer = 0;
	static char		*current_pos = NULL;
	char			*newline_pos = NULL;
	char			*result = NULL;
	char			*new_result;
	size_t			current_line_length = 0;
	size_t			segment_length;

	while (1)
	{
		if (bytes_in_buffer == 0)
		{
			bytes_in_buffer = read(fd, buffer, sizeof(buffer) - 1);
			if (bytes_in_buffer <= 0)
			{
				return (result);
			}
			buffer[bytes_in_buffer] = '\0';
			current_pos = buffer;
		}
		newline_pos = ft_strchr(current_pos, '\n');
		if (newline_pos != NULL)
		{
			*newline_pos = '\0';
		}
		if (newline_pos != NULL) 
		{
			segment_length = newline_pos - current_pos;
		}
		else 
		{
			segment_length = bytes_in_buffer;
		}
		new_result = malloc(current_line_length + segment_length + 1);
		if (result != NULL) {
			ft_memcpy(new_result, result, current_line_length);
			free(result);
    }
    ft_memcpy(new_result + current_line_length, current_pos, segment_length);
    result = new_result;
    current_line_length += segment_length;

		if (newline_pos != NULL)
		{
			current_pos = newline_pos + 1;
			bytes_in_buffer -= (newline_pos - buffer + 1);
			break; 
		}
		else
		{
			bytes_in_buffer = 0;
		}
	}

	result[current_line_length] = '\0'; 
	return result;
}

int main(void)
{
	int fd;
	fd = open_file("text.txt");
	if (fd == -1)
	{
		printf("Failed to open the file\n");
		return 1;
	}

	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));

	close_file(fd);
	return 0;
}
