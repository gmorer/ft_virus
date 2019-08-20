#ifndef FT_VIRUS_H
# define FT_VIRUS_H

# include <elf.h>

# define SYS_READ 0
# define SYS_WRITE 1
# define SYS_OPEN 2
# define SYS_CLOSE 3
# define SYS_LSEEK 8
# define SYS_EXIT 60
# define SYS_GETUID 102
# define SYS_GETDENT64 217
# define O_RDONLY 0
# define O_WRONLY 1
# define O_RDWR 2
# define O_DIRECTORY 0x10000
# define DT_REG 8

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

# define INFESTED_DIR "/tmp/"

typedef unsigned long long u64;
typedef long long s64;
typedef unsigned int size_t;
typedef signed long off_t;

struct linux_dirent64 {
	u64        d_ino;    // 64-bit inode number
	s64        d_off;    // 64-bit offset to next structure
	unsigned short d_reclen; // Size of this dirent
	unsigned char  d_type;   // File type
	char           d_name[]; // Filename (null-terminated)
};


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
size_t syscall6(int syscall, void *arg1, size_t arg2, int arg3, int arg4, int arg5, off_t arg6);

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
