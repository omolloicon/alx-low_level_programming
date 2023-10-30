#include "main.h"

/**
 * append_text_to_file - append file content
 *
 * @filename: file name
 * @text_content: file content
 * Return: 1 only if succes, else -1.
 */

int append_text_to_file(const char *filename, char *text_content)
{
	int wee, cap, scans;

	if (!filename)
		return (-1);
	wee = open(filename, O_WRONLY | O_APPEND);
	if (wee == -1)
		return (-1);
	if (text_content)
	{
		for (cap = 0; text_content[cap]; cap++)
			;
		scans = write(wee, text_content, cap);
		if (scans == -1)
			return (-1);
	}
	close(wee);
	return (1);
}
