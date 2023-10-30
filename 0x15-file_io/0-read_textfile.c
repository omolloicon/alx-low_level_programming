#include "main.h"

/**
 * read_textfile - print text to position standard output of txt.
 *
 * @filename: file name
 * @letters: letter tally
 * Return: success
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	int bav;
	ssize_t rpa, capb;
	char *sto;

	if (filename == 0)
		return (0);
	bav = open(filename, O_RDONLY);
	if (bav == -1)
		return (0);
	sto = malloc(sizeof(char) * letters);
	if (sto == NULL)
	{
		close(bav);
		return (0);
	}
	rpa = read(bav, sto, letters);
	close(bav);
	if (rpa == -1)
	{
		free(sto);
		return (0);
	}
	capb = write(STDOUT_FILENO, sto, rpa);
	free(sto);
	if (rpa != capb)
		return (0);
	return (capb);
}
