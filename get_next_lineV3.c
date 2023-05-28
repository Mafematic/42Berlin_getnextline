#define BUFFER_SIZE 100

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int open_file(char *file_path)
{
	int fd;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	return (fd);
}

int close_file(int fd)
{
	if (close(fd) == -1)
		return (0);
	return (1);
}

char *ft_strchr(const char *s, int c)
{
	int i;
	unsigned char ch;

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


#define BUFFER_SIZE 100

char *get_next_line(int fd)
{
	char buffer[BUFFER_SIZE + 1];
	ssize_t bytes_read;
	char *newline_pos;
	char *line = NULL;
	int is_line_complete = 0;

	while (!is_line_complete)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			write(1, "Failed to read file", 19);
			if (line)
				free(line);
			return NULL;
		}
		buffer[bytes_read] = '\0';

		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos != NULL)
		{
			*newline_pos = '\0';
			is_line_complete = 1;
		}

		if (line == NULL)
		{
			line = strdup(buffer);
		}
		else
		{
			line = realloc(line, strlen(line) + strlen(buffer) + 1);
			strcat(line, buffer);
		}
	}
	return line;
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
