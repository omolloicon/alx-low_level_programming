#include "main.h"
#include <stdio.h>

/**
 * file_e - erroe check
 * @source: from.
 * @dest: to.
 * @argv: arguments vector.
 * Return: null.
 */

void file_e(int source, int dest, char *argv[])
{
	if (source == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}
	if (dest == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		exit(99);
	}
}

/**
 * main - check holbeerton
 * @argc: number of arguments.
 * @argv: arguments vector.
 * Return: 0.
 */

int main(int argc, char *argv[])
{
	int source, dest, erroor;
	ssize_t c_count, each;
	char baf[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "%s\n", "Usage: cp file_from file_to");
		exit(97);
	}
	source = open(argv[1], O_RDONLY);
	dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0664);
	file_e(source, dest, argv);
	c_count = 1024;
	while (c_count == 1024)
	{
		c_count = read(source, baf, 1024);
		if (c_count == -1)
			file_e(-1, 0, argv);
		each = write(dest, baf, c_count);
		if (c_count == -1)
			file_e(0, -1, argv);
	}
	erroor = close(source);
	if (erroor == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", source);
		exit(100);
	}
	erroor = close(dest);
	if (erroor == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", source);
		exit(100);
	}
	return (0);
}
