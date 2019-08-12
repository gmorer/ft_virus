#ifndef FT_VIRUS_H
# define FT_VIRUS_H

# define SYS_READ 0
# define SYS_WRITE 1
# define SYS_OPEN 2
# define SYS_CLOSE 3
# define SYS_LSEEK 8
# define SYS_GETUID 102
# define SYS_GETDENT64 217
# define O_RDONLY 0
# define O_WRONLY 1
# define O_RDWR 2
# define O_DIRECTORY 0x10000

# define FORCE_INLINE __attribute__((always_inline)) inline

# define WRITE(fd, buffer, len) syscall(SYS_WRITE, fd, buffer, len)
# define OPEN(pathname, flags) syscall1(SYS_OPEN, pathname, flags)

# define INFESTED_DIR "/tmp"

typedef unsigned long long u64;
typedef long long s64;

struct linux_dirent64 {
	u64        d_ino;    // 64-bit inode number
	s64        d_off;    // 64-bit offset to next structure
	unsigned short d_reclen; // Size of this dirent
	unsigned char  d_type;   // File type
	char           d_name[]; // Filename (null-terminated)
};

typedef unsigned int size_t;

typedef struct	s_data
{
	int	key;
	int	decrypt_start;
}		t_data;


/* syscalls */
size_t syscall(int syscall, int arg1, char *arg2, size_t arg3);
int syscall1(int syscall, char *arg1, int arg2);

void payload(void);
void payload_end(void);

int finder(int fd);


#endif
