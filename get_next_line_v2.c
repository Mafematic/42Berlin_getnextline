#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

char *get_next_line(int fd)
{
	char buffer[100];
	int has_newline = 0;
	static char *newline_pos;

	ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read == -1)
	{
		write(1, "Failed to read file", 19);
	}

	// Check Buffer for newline
	buffer[bytes_read] = '\0';

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos != NULL)
	{
		*newline_pos = '\0';
		printf("%s\n", buffer);
		//newline_pos += 1;
	}
	else
	{
		// No newline found, print the entire buffer
		printf("%s", buffer);
	}
	return NULL;
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

	get_next_line(fd); 
	get_next_line(fd); 
	get_next_line(fd); 
	get_next_line(fd); 

	close_file(fd);
	return 0;
}
