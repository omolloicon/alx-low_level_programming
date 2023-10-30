#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void p_magic(unsigned char *e_ident);
void p_class(unsigned char *e_ident);
void p_data(unsigned char *e_ident);
void p_version(unsigned char *e_ident);
void p_abi(unsigned char *e_ident);
void p_osabi(unsigned char *e_ident);
void p_type(unsigned int e_type, unsigned char *e_ident);
void p_entry(unsigned long int e_entry, unsigned char *e_ident);
void c_elf(int des);

/**
 * check_elf - search for an ELF file.
 * @e_ident: magic number
 * Description: If not true - exit code 98.
 */

void check_elf(unsigned char *e_ident)
{
	int pos;

	for (pos = 0; pos < 4; pos++)
	{
		if (e_ident[pos] != 127 &&
		    e_ident[pos] != 'E' &&
		    e_ident[pos] != 'L' &&
		    e_ident[pos] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * p_magic - Prints ELF header.
 * @e_ident: A pointer to an array containing the ELF magic numbers.
 * Description: seperates magic nums
 */

void p_magic(unsigned char *e_ident)
{
	int pos;

	printf("  Magic:   ");
	for (pos = 0; pos < EI_NIDENT; pos++)
	{
		printf("%02x", e_ident[pos]);
		if (pos == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * p_class - ELF class.
 * @e_ident: ELF class.
 */

void p_class(unsigned char *e_ident)
{
	printf("  Class:                             ");
	switch (e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * p_data - display data of an ELF header.
 * @e_ident:  ELF class pointer.
 */

void p_data(unsigned char *e_ident)
{
	printf("  Data:                              ");
	switch (e_ident[EI_DATA])
	{
	case ELFDATANONE:
		printf("none\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * p_version - Elf version dispaly
 * @e_ident: version.
 */

void p_version(unsigned char *e_ident)
{
	printf("  Version:                           %d",
	       e_ident[EI_VERSION]);
	switch (e_ident[EI_VERSION])
	{
	case EV_CURRENT:
		printf(" (current)\n");
		break;
	default:
		printf("\n");
		break;
	}
}

/**
 * p_osabi - OS/ABI of ELF.
 * @e_ident: ELF version.
 */

void p_osabi(unsigned char *e_ident)
{
	printf("  OS/ABI:                            ");
	switch (e_ident[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone App\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
 * p_abi - displays the ABI.
 * @e_ident: A pointer to ELF ABI version.
 */

void p_abi(unsigned char *e_ident)
{
	printf("  ABI Version:                       %d\n",
	       e_ident[EI_ABIVERSION]);
}

/**
 * p_type - display the type.
 * @e_type: The ELF type.
 * @e_ident: the ELF class.
 */

void p_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;
	printf("  Type:                              ");
	switch (e_type)
	{
	case ET_NONE:
		printf("NONE (None)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("<unknown: %x>\n", e_type);
	}
}

/**
 * p_entry - display the entry point.
 * @e_entry: The address
 * @e_ident:  an array of the ELF class.
 */

void p_entry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf("  Entry point address:               ");
	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) |
			  ((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}
	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)e_entry);
	else
		printf("%#lx\n", e_entry);
}

/**
 * check_elf - to shut down an ELF file.
 * @des: tells all.
 * Description: If the file cannot be closed - exit code 98.
 */

void check_elf(int des)
{
	if (close(des) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", des);
		exit(98);
	}
}

/**
 * main - head info
 * @argc: arg tally.
 * @argv: arg store.
 * Return: 0 if done
 * Description: If it fails - exit code 98.
 */

int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;

	int j, k;

	j = open(argv[1], O_RDONLY);
	if (j == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		check_elf(j);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	k = read(j, header, sizeof(Elf64_Ehdr));
	if (k == -1)
	{
		free(header);
		check_elf(j);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}
	check_elf(header->e_ident);
	printf("ELF Header:\n");
	p_magic(header->e_ident);
	p_class(header->e_ident);
	p_data(header->e_ident);
	p_version(header->e_ident);
	p_osabi(header->e_ident);
	p_abi(header->e_ident);
	p_type(header->e_type, header->e_ident);
	p_entry(header->e_entry, header->e_ident);

	free(header);

	c_elf(j);

	return (0);
}
