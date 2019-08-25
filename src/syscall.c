#include "ft_virus.h"

u64 syscall3(int syscall, u64 arg1, u64 arg2, u64 arg3)
{
	u64 ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1), "S"(arg2), "d"(arg3)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

u64 syscall2(int syscall, u64 arg1, u64 arg2)
{
	u64 ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1), "S"(arg2)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

u64 syscall1(int syscall, u64 arg1)
{
	u64 ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

/*
u64 syscall6(int syscall, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6)
{
	u64	ret;

	register long rdi asm("rdi") = (long int)arg1;
	register long rsi asm("rsi") = arg2;
	register long rdx asm("rdx") = arg3;
	register long r10 asm("r10") = arg4;
	register long r9 asm("r9") = arg5;
	register long r8 asm("r8") = arg6;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}
*/
