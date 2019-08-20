# include "ft_virus.h"

int FORCE_INLINE get_binary(int fd)
{
	size_t file_size;
	struct stat buffer;
	char		*file;

	if (FSTAT(fd, &buffer) < 0)
		return (0);
	file_size = buffer.st_size;
	WRITE(1, "size: ", 6);
	ft_putnbr(file_size);
	WRITE(1, "\n", 1);
	file = MMAP(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (file == MAP_FAILED)
		return (0);
	ft_putnbr((int)file);
	WRITE(1, file, file_size);
	//MUNMAP(file, file_size);
	return (1);
}


void inject(int file_fd)
{
	get_binary(file_fd);
	// TODO
	/*
	getBinary();
	find_cave();
	change_sections_header(); // to make the cave executable
	fill_payload(); // mprotect us!
	copy_payload(); // memcpy you know...
	*/
	;
}
