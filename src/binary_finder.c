#include "ft_virus.h"

# define BUF_SIZE 1024


int ft_strlen(char *str)
{
	int res;

	res = 0;
	while(str[res])
		res += 1;
	return (res);
}

int FORCE_INLINE finder(int fd)
{
	int nread;
	char buf[BUF_SIZE];
	int bpos;
	struct linux_dirent64 *d;

	while(1)
	{
		nread = syscall(SYS_GETDENT64, fd, buf, BUF_SIZE);
		if (!nread || nread == -1)
			return (0);
		bpos = 0;
		while (bpos < nread)
		{
			d = (struct linux_dirent64*)(buf + bpos);
			WRITE(1, d->d_name, ft_strlen(d->d_name));
			WRITE(1, "\n", 1);
			bpos += d->d_reclen;
		}
	}
}
