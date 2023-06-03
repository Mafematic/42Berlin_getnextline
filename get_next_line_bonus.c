#include "get_next_line_bonus.h"

char	*extract_line_from_buffer(char *buffer)
{
	int		i;
	char	*line;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*move_pointer(char *ptr_position)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (ptr_position[i] && ptr_position[i] != '\n')
		i++;
	if (ptr_position[i] == '\0')
	{
		free(ptr_position);
		return (NULL);
	}
	if (ptr_position[i] == '\n')
		i++;
	new_buffer = malloc(sizeof(char) * (ft_strlen(ptr_position) - i) + 1);
	if (!new_buffer)
		return (NULL);
	j = 0;
	while (ptr_position[i + j])
	{
		new_buffer[j] = ptr_position[i + j];
		j++;
	}
	new_buffer[j] = '\0';
	free(ptr_position);
	return (new_buffer);
}

char	*read_append_to_buffer(int fd, char **buffer, char **line)
{
	char	*tmp_line;
	int		bytes_read;

	tmp_line = NULL;
	bytes_read = 1;
	while (!(ft_strchr(buffer[fd], '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, *line, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*line);
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		(*line)[bytes_read] = '\0';
		tmp_line = ft_strjoin(buffer[fd], *line);
		if (tmp_line)
		{
			free(buffer[fd]);
			buffer[fd] = tmp_line;
		}
	}
	free(*line);
	return (buffer[fd]);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024] = {NULL};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	buffer[fd] = read_append_to_buffer(fd, buffer, &line);
	if (!buffer[fd])
		return (NULL);
	line = extract_line_from_buffer(buffer[fd]);
	buffer[fd] = move_pointer(buffer[fd]);
	if (!buffer[fd] || buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>

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
	{
		return (0);
	}
	return (1);
}

int	main(void)
{
	int	fd;

	char *line; 
	fd = open_file("text");
	if (fd <= 0)
	{
		printf("Could not open file!\n"); 
		return (1); 
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line); 
	}
	if (close_file(fd) == 0)
	{
		printf("Could not close file.\n");
		return (1);
	}
	return (0); 
}
*/