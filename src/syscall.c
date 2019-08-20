#include "ft_virus.h"

size_t syscall0(int syscall, int arg1, char *arg2, size_t arg3)
{
	size_t ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1), "S"(arg2), "d"(arg3)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

int syscall1(int syscall, char *arg1, int arg2)
{
	int ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1), "S"(arg2)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

size_t syscall2(int syscall, int arg1)
{
	size_t ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

size_t syscall3(int syscall, int arg1, void *arg2)
{
	size_t ret;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1), "S"(arg2)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}

void	*syscall6(int syscall, void *arg1, size_t arg2, int arg3, int arg4, int arg5, off_t arg6)
{
	register long r10 asm("r10") = arg4;
	register long r9 asm("r9") = arg5;
	register long r8 asm("r8") = arg6;

	asm volatile
		(
		 "syscall"
		 : "=a" (ret)
		 : "0"(syscall), "D"(arg1), "S"(arg2), "d"(arg3)
		 : "cc", "rcx", "r11", "memory"
		);
	return ret;
}
