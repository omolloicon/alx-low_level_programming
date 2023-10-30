#include "main.h"

/**
 * create_file - generates file.
 * @filename: file name.
 * @text_content: file content.
 * Return: 1 only if success, else -1.
 */

int create_file(const char *filename, char *text_content)
{
	int nav, sto_m, wo;

	if (!filename)
		return (-1);
	nav = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (nav == -1)
		return (-1);
	if (!text_content)
		text_content = "";
	for (sto_m = 0; text_content[sto_m]; sto_m++)
		;
	wo = write(nav, text_content, sto_m);
	if (wo == -1)
		return (-1);
	close(nav);
	return (1);
}
