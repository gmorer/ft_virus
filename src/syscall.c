#include "ft_virus.h"

size_t FORCE_INLINE syscall0(int syscall, int arg1, char *arg2, size_t arg3)
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

int FORCE_INLINE syscall1(int syscall, char *arg1, int arg2)
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

size_t FORCE_INLINE syscall2(int syscall, int arg1)
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
