#include "ft_virus.h"

u64 syscall4(int syscall, u64 arg1, u64 arg2, u64 arg3, u64 arg4)
{
	u64 ret;

	register long r10 asm("r10") = arg4;
	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1), "S"(arg2), "d"(arg3), "r" (r10)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

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

u64 syscall0(int syscall)
{
	u64 ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}